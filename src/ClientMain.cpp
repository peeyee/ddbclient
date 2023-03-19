#include <iostream>
#include "ParseOptions.h"
#include "Client.h"

const std:string VERSION = "0.1";

inline void showPrompt();

int main(int argc, char* argv){
    using namespace std;
    const prompt = "> ";
    ParseOption parser;
    variables_map vm = parser.parse(argc, argv);
    string host = vm["host"].as<string>();
    int port = vm["port"].as<int>();
    string username =  vm["username"].as<string>();
    string password =  vm["password"].as<string>();
    Client client;
    client.connect(host, port, username, password);
    if(client.isConnected){
        cout << "Welcome to DolphinDB " << client.run("verion()") -> getString() << endl;
    }else{
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
                ConstantSP rst = client.runInteractive(cmd);
                cout << rst -> getString() << endl;
            }
            catch(const std::exception& e)
            {
                cout << "run command failed: " << e.what() << '\n';
            }
                
        }
    }else{

    }

    return 0;
}

showPrompt(){
    std::cout<< "> " << std::endl;
}