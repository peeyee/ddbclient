#include <iostream>
#include "Client.h"
#include "DolphinDB.h"
#include  <boost/program_options.hpp>
namespace po = boost::program_options;
const std::string VERSION = "0.1";

inline void showPrompt();

int main(int argc, char* argv[]){
    using namespace std;
    po::options_description desc("DolphinDB client " + VERSION);
    desc.add_options()
        ("help", "show help message")
        ("host,h", po::value<std::string>(), "the ip/hostname connect to")
        ("port,p", po::value<int>(), "the port of DolphinDB node")
        ("username,u", po::value<std::string>(), "username")
        ("password", po::value<std::string>(), "password");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    string host, username, password;
    int port;
    try{
	if(argc < 4 || vm.count("help")){
            cout << desc << endl;
            return 0;
        }
        host = vm["host"].as<string>();
        port = vm["port"].as<int>();
        username =  vm["username"].as<string>();
        password =  vm["password"].as<string>();
    }catch(exception& e){
        cout << "parse input failed, exit." << endl;
        exit(2); 
    }    
    Client client;
    client.connect(host, port, username, password);
    if(client.isConnected()){
        cout << "Welcome to DolphinDB " << client.runInteractive("version()") -> getString() << endl;
    }else{
        cout << "failed connect to DolphinDB " + host + ":" + to_string(port) << endl;
        exit(1);
    }
        
    if(client.isInteractiveMode()){        
        while(true){
            showPrompt();
            string cmd;
            getline(cin, cmd);
            if(cmd == "q" || cmd == "quit"){
                cout << "Bye." << endl;
                return 0;
            }
            try
            {
                dolphindb::ConstantSP rst = client.runInteractive(cmd);
                cout << rst -> getString() << endl;
            }
            catch(exception& e)
            {
                cout << "run command failed: " << e.what() << '\n';
            }
                
        }
    }else{

    }

    return 0;
}

void showPrompt(){
    std::cout << "> " ;
}

