#include <string>
#include "DolphinDB.h"
#include "Util.h"
#include "Client.h"

bool Client::connect(string host, int port, string username, string password){
      bool isConnect = this -> conn_.connect(host, port, username, password);
      this -> connected_ = isConnect;
      return isConnect;
}

dolphindb::ConstantSP Client::runInteractive(string cmd){
      return this -> conn_.run(cmd);
}

dolphindb::ConstantSP Client::runNonInteractive(string cmd){
      return this -> conn_.run(cmd);
}
