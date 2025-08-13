#include <iostream>
#include <string>
#include "Client.h"
#include "FileReader.h"
#include "DolphinDB.h"
#include "cmdline.h"
#include "linenoise.h"
#include "StringUtil.h"
#include <pwd.h>
#include <unistd.h> 

const std::string VERSION = "0.4.0";

inline static void showPrompt(); 
static void showBanner();
void completionHook(const char* input, linenoiseCompletions* lc);

static std::vector<std::string> keyWords;


int main(int argc, char* argv[]){
    using namespace std;
    using namespace cli;
    
    linenoiseSetCompletionCallback(completionHook);
    struct passwd *pw = getpwuid(geteuid());
    string historyFile = string(pw -> pw_dir) + string("/.ddbclient_history");
    linenoiseHistoryLoad(historyFile.c_str());

    cmdline::parser parser;
    parser.add<string>("host", 'h', "ip/hostname of server", true, "");
    parser.add<int>("port", 'p', "the port of node", false, 8848, cmdline::range(1, 65535));
    parser.add<string>("username", 'u', "username", true);
    parser.add<string>("password", 'P', "password", true);
    parser.add<string>("file", 'f', "filename of the script to be executed", false);
    parser.add<string>("script", 's', "the script to execute", false);
    parser.add("secure", '\0', "use SSL connection");

    parser.parse_check(argc, argv);

    string host, username, password;
    int port;
    bool useSSL = false;
    try{
        if(argc < 4 || parser.exist("help")){
                cout << parser.usage() << endl;
            return 0;
        }
        host = parser.get<string>("host");
        port =  parser.get<int>("port");;
        username =  parser.get<string>("username");
        password =  parser.get<string>("password");
        if(parser.exist("secure")){
            useSSL = true;
        }
    }catch(exception& e){
        cout << "Parse input failed, exit." << endl;
        exit(128); 
    }    
   
    Client client(useSSL); 
    client.connect(host, port, username, password);
    if(!client.isConnected()){
        cout << "Failed connect to DolphinDB " + host + ":" + to_string(port) << endl;
        exit(130);
    }

    if(parser.exist("file") && parser.exist("script")){
        cout << "Ambiguous parameter: file and script, keep one of them!" << endl;
        exit(128);
    }else if (parser.exist("file"))
    {
        FileReader f;
        try{
            string script = f.read(parser.get<string>("file"));
            dolphindb::ConstantSP result = client.runNonInteractive(script);
            cout << result -> getString() << endl;
            return 0;
        }catch(exception& e){
            cout << "ERROR " << e.what() << '\n';
            exit(140);
        }
    }else if(parser.exist("script")){
        string script = parser.get<string>("script");
        try{
            dolphindb::ConstantSP result = client.runNonInteractive(script);
            cout << result -> getString() << endl;
            return 0;
        }catch(exception& e){
            cout << "ERROR " << e.what() << '\n';
            exit(140);
        }
    }
    
    if(client.isInteractiveMode()){
        showBanner();
        cout << "Welcome to DolphinDB " ;
        dolphindb::ConstantSP v = client.runNonInteractive("version()");
        cout << v->getString() << endl << endl;


        client.getKeyWords(keyWords);
        string cmd;
        bool isMultiLine = false;

        while(true){
            char* line = linenoise("cli> ");
            string lineStr;
            //process EOF
            if(line != nullptr && *line){
                linenoiseHistoryAdd(line);
            }else{
                continue;
            }
            unique_ptr<char> pLine(line);
            lineStr = string(line);

            if(lineStr == "quit"){
                linenoiseHistorySave(historyFile.c_str());
                cout << "Bye." << endl;
                break;
            }

            bool endWithBackslash = StringUtil::endsWith(lineStr, "\\") ? true : false;

            if (isMultiLine && endWithBackslash)
            {
                string validStr = lineStr.substr(0, lineStr.length() - 1);
                cmd += validStr;
                continue;
            }else if(isMultiLine && !endWithBackslash){
                cmd += lineStr;
            }else if(!isMultiLine && endWithBackslash){
                isMultiLine = true;
                cmd = lineStr.substr(0, lineStr.length() - 1);
                continue;
            }else{
                cmd = lineStr;
            }

            try
            {
                if(cmd[0] == '!'){
                    std::string shellCmd = cmd.substr(1, cmd.size() - 1);
                    int hasError = client.runShell(shellCmd);
                    if(hasError){
                        cout << "[" +  cmd + "] execute failed." << endl << endl;
                    }
                    cout << endl;
                }else{
                    client.runInteractive(cmd);
                }
            }
            catch(const std::exception& e)
            {
                cout << "ERROR: " << e.what() << endl << endl;
            }
            isMultiLine = false;
            cmd = "";
        }
    }
    {
        client.close();
    }
    return 0;
}

static void showPrompt(){
    std::cout << ">  " ;
}

static void showBanner(){
    std::cout << "Ddbclient version " << VERSION << std::endl;
    std::cout << "Github: https://github.com/peeyee/ddbclient.git" << std::endl;
    std::string banner = R"(
-----------------------------------------------------------
  _____          _         _      _         _____   ____  
 |  __ \        | |       | |    (_)       |  __ \ |  _ \ 
 | |  | |  ___  | | _ __  | |__   _  _ __  | |  | || |_) |
 | |  | | / _ \ | || '_ \ | '_ \ | || '_ \ | |  | ||  _ < 
 | |__| || (_) || || |_) || | | || || | | || |__| || |_) |
 |______/ \___/ |_|| .__/ |_| |_||_||_| |_||______/|_____/ 
                   | |                                    
                   |_|                            

-----------------------------------------------------------
)";
    std::cout << banner << std::endl;
}



void completionHook(const char* input, linenoiseCompletions* lc) {
    std::string currentInput(input);  
    
    if(cli::StringUtil::contains(currentInput, ".")){
        size_t i = currentInput.find_last_of(".");
        currentInput = currentInput.substr(i+1);
    }

    for (const auto& func : keyWords) {
        if (func.find(currentInput) == 0) {
            linenoiseAddCompletion(lc, func.c_str());
        }
    }
}