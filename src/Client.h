#include <string>
#include "DolphinDB.h"
#include "Util.h"

class Client
{
    private:
        bool isInactive_;
        bool connected_;
        DBConnection conn;

    public:
        Client():connected_(false){};
        ~Client() override;
        ConstantSP runInteractive(std::string cmd) throw;
        bool isInteractiveMode();
        ConstantSP runNonInteractive(std::string cmd) throw;
        bool connect(string host, int port, string username, string password);
        bool isConnected(){
            return connected_;
        };
}