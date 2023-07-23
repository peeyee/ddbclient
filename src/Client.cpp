#include <string>
#include "DolphinDB.h"
#include "Util.h"
#include "Client.h"

bool Client::connect(string host, int port, string username, string password){
      bool isConnect = this -> conn_.connect(host, port, username, password);
      this -> connected_ = isConnect;
      return isConnect;
}

void Client::runInteractive(string cmd){
      dolphindb::ConstantSP result =  this -> conn_.run(cmd);
      string fmtResult = result -> getString();
      if(fmtResult.length() == 0){
            return;
      }
      if( fmtResult.back() == '\n'){
            fmtResult.pop_back();
      }
      std::cout << fmtResult << std::endl;
}

dolphindb::ConstantSP Client::runNonInteractive(string cmd){
      return this -> conn_.run(cmd);
}
