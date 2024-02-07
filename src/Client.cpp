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
      //this -> history.add(cmd);

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

std::vector<std::string> Client::getKeyWords(std::vector<std::string> & words){
      std::string sql = R"(
            select name 
            from defs() 
            where strlen(name) >= 3 
            and regexFind(name, "^[a-zA-Z0-9]+") >= 0
            and userDefined = false)";

      auto rst = this -> conn_.run(sql);
      dolphindb::VectorSP vp = rst->getColumn(0);
      std::vector<std::string> allKeyWords;
      for(int i = 0; i < vp ->size(); ++i){
            words.emplace_back(vp->getString(i));
      }
};