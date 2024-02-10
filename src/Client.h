#include <string>
#include "DolphinDB.h"
#include "Util.h"
#include "CommandHistory.h"
namespace cli{
class Client
{
    private:
        bool isInactive_;
        bool connected_;
        dolphindb::DBConnection conn_;
        CommandHistory history;

    public:
        Client():connected_(false),isInactive_(true){};
        ~Client(){};
        void runInteractive(std::string cmd); 
        bool isInteractiveMode(){ return isInactive_; };
        dolphindb::ConstantSP runNonInteractive(std::string cmd);
        bool connect(string host, int port, string username, string password);
        bool isConnected(){
            return connected_;
        };
        void close(){
            this -> history.store();
            conn_.close();
        }
        void getKeyWords(std::vector<std::string> & words);
};
}