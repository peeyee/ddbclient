#include <string>
#include "DolphinDB.h"
#include "Util.h"

class Client
{
    private:
        bool isInactive_;
        bool connected_;
        dolphindb::DBConnection conn_;

    public:
        Client():connected_(false),isInactive_(true){};
        ~Client(){};
        dolphindb::ConstantSP runInteractive(std::string cmd); 
        bool isInteractiveMode(){ return isInactive_; };
        dolphindb::ConstantSP runNonInteractive(std::string cmd);
        bool connect(string host, int port, string username, string password);
        bool isConnected(){
            return connected_;
        };
};
