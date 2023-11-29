#include <iostream>
#include "Client.h"
#include "FileReader.h"
#include "DolphinDB.h"
#include  <boost/program_options.hpp>
namespace po = boost::program_options;
const std::string VERSION = "0.1.alpha";

inline void showPrompt();
void showBanner();

int main(int argc, char* argv[]){
    using namespace std;
    po::options_description desc("DolphinDB client " + VERSION);
    desc.add_options()
        ("help", "show help message")
        ("host,h", po::value<std::string>(), "the ip/hostname connect to")
        ("port,p", po::value<int>(), "the port of DolphinDB node")
        ("username,u", po::value<std::string>(), "username")
        ("password", po::value<std::string>(), "password")
        ("file,f",  po::value<std::string>(), "read script from a file")
        ("script,s",  po::value<std::string>(), "the script to run");
    po::variables_map vm;
    string host, username, password;
    int port;
    try{
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        if(argc < 4 || vm.count("help")){
                cout << desc << endl;
            return 0;
        }
        host = vm["host"].as<string>();
        port = vm["port"].as<int>();
        username =  vm["username"].as<string>();
        password =  vm["password"].as<string>();
    }catch(exception& e){
        cout << "Parse input failed, exit." << endl;
        exit(128); 
    }    
    Client client;
    client.connect(host, port, username, password);
    if(!client.isConnected()){
        cout << "Failed connect to DolphinDB " + host + ":" + to_string(port) << endl;
        exit(130);
    }

    if(vm.count("file") && vm.count("script")){
        cout << "Confict argument: file and script, choose either of them!" << endl;
        exit(128);
    }

    if(vm.count("file")){
        FileReader f;
        try{
            string script = f.read(vm["file"].as<string>());
            dolphindb::ConstantSP result = client.runNonInteractive(script);
            cout << result -> getString() << endl;
            return 0;
        }catch(exception& e){
            cout << "run command failed: " << e.what() << '\n';
            exit(140);
        }
    }

    if(vm.count("script")){
        string script = vm["script"].as<string>();
        try{
            dolphindb::ConstantSP result = client.runNonInteractive(script);
            cout << result -> getString() << endl;
            return 0;
        }catch(exception& e){
            cout << "run command failed: " << e.what() << '\n';
            exit(140);
        }
    }
    
    if(client.isInteractiveMode()){
        showBanner();
        cout << "Welcome to DolphinDB ";
        client.runInteractive("version()");    
        while(true){
            showPrompt();
            string cmd;
            getline(cin, cmd);
            if(cmd == "q" || cmd == "quit"){
                cout << "Bye." << endl;
                break;
            }
            try
            {
                client.runInteractive(cmd);
            }catch(exception& e)
            {
                cout << "run command failed: " << e.what() << '\n';
            }
        }
    }

    client.close();
    return 0;
}

void showPrompt(){
    std::cout << ">  " ;
}

void showBanner(){
    std::string banner = R"(
============================================================
  _____          _         _      _         _____   ____  
 |  __ \        | |       | |    (_)       |  __ \ |  _ \ 
 | |  | |  ___  | | _ __  | |__   _  _ __  | |  | || |_) |
 | |  | | / _ \ | || '_ \ | '_ \ | || '_ \ | |  | ||  _ < 
 | |__| || (_) || || |_) || | | || || | | || |__| || |_) |
 |_____/  \___/ |_|| .__/ |_| |_||_||_| |_||_____/ |____/ 
                   | |                                    
                   |_|                            

official website: https://www.dolphindb.com/
github: https://github.com/dolphindb
support email：support@dolphindb.com        
============================================================
)";
    std::cout << banner << std::endl;
}