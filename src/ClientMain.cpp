#include <iostream>
#include "Client.h"
#include "FileReader.h"
#include "DolphinDB.h"
#include "cmdline.h"
#include "readline/readline.h"
#include "readline/history.h"
#include <pwd.h>
#include <unistd.h> 

const std::string VERSION = "0.1.1";

inline void showPrompt();
void showBanner();
char** myCompletion(const char *text, int start, int end);
char * command_generator(const char *text, int state);

char** keyWords;


int main(int argc, char* argv[]){
    using namespace std;

    cmdline::parser parser;
    parser.add<string>("host", 'h', "ip/hostname of server", true, "");
    parser.add<int>("port", 'p', "the port of node", true, 8848, cmdline::range(1, 65535));
    parser.add<string>("username", 'u', "username", true);
    parser.add<string>("password", 'P', "password", true);
    parser.add<string>("file", 'f', "filename of the script to be executed", false);
    parser.add<string>("script", 's', "the script to execute", false);

    parser.parse_check(argc, argv);

    string host, username, password;
    int port;
    try{
        if(argc < 4 || parser.exist("help")){
                cout << parser.usage() << endl;
            return 0;
        }
        host = parser.get<string>("host");
        port =  parser.get<int>("port");;
        username =  parser.get<string>("username");
        password =  parser.get<string>("password");
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

    if(parser.exist("file") && parser.exist("script")){
        cout << "Ambiguous parameter: file and script, keep one of them!" << endl;
        exit(128);
    }else if (parser.exist("file"))
    {
        FileReader f;
        try{
            string script = f.read(parser.get<string>("filename"));
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
        cout << "Welcome to DolphinDB ";
        client.runInteractive("version()");
        struct passwd *pw = getpwuid(geteuid());
        string historyFile = string(pw -> pw_dir) + string("/.ddbclient_history");
        rl_attempted_completion_function = myCompletion;
        //just read last 100 command history
        read_history_range (historyFile.c_str(), 0, 99);
        vector<string> keyWords;
        client.getKeyWords(keyWords);
        
        while(true){
            char* line = readline("> ");
            if(*line){
                add_history(line);
            }
            unique_ptr<char> pLine(line);
            string cmd(line);

            if(cmd == "quit"){
                write_history(historyFile.c_str());
                cout << "Bye." << endl;
                break;
            }

            try
            {
                client.runInteractive(cmd);
            }catch(exception& e)
            {
                cout << "ERROR " << e.what() << '\n';
            }
        }
    }
    {
        client.close();
    }
    return 0;
}

void showPrompt(){
    std::cout << ">  " ;
}

void showBanner(){
    std::string banner = R"(
-----------------------------------------------------------
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
support email: support@dolphindb.com

-----------------------------------------------------------
)";
    std::cout << banner << std::endl;
}

char** myCompletion(const char *text, int start, int end){
 char **matches;

  matches = (char **)NULL;

  /* If this word is at the start of the line, then it is a command
     to complete.  Otherwise it is the name of a file in the current
     directory. */
  if (start == 0)
    matches = rl_completion_matches (text, command_generator);

  return (matches);
}

    
char * command_generator(const char *text, int state){
  static int list_index, len;
  char *name;

  /* If this is a new word to complete, initialize now.  This includes
     saving the length of TEXT for efficiency, and initializing the index
     variable to 0. */
  if (!state)
    {
      list_index = 0;
      len = strlen (text);
    }

  /* Return the next name which partially matches from the command list. */
  while (name = keyWords[list_index])
    {
      list_index++;

      if (strncmp (name, text, len) == 0)
        return (dupstr(name));
    }

  /* If no names matched, then return NULL. */
  return ((char *)NULL);
}