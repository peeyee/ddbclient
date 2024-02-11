#include <string>
#include "DolphinDB.h"
#include "Util.h"
#include "Client.h"
#include <chrono>
#include <iomanip>
namespace cli{

bool Client::connect(string host, int port, string username, string password){
      bool isConnect = this -> conn_.connect(host, port, username, password);
      this -> connected_ = isConnect;
      return isConnect;
}

void Client::runInteractive(string cmd){
      auto start = std::chrono::high_resolution_clock::now();  
      dolphindb::ConstantSP result =  this -> conn_.run(cmd);
      string fmtResult = result -> getString();
      auto end = std::chrono::high_resolution_clock::now(); 
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
      double seconds = static_cast<double>(duration) / 1000.0; 
      std::cout << fmtResult << std::endl;
      std::cout << std::fixed << std::setprecision(3);
      std::cout << "OK. Elapsed: " << seconds << " sec." << std::endl << std::endl;
}

dolphindb::ConstantSP Client::runNonInteractive(string cmd){
      return this -> conn_.run(cmd);
}

void Client::getKeyWords(std::vector<std::string> & words){
      std::string sql = R"(
      select name 
      from defs() 
      where strlen(name) >= 3 and regexFind(name, "^[a-zA-Z0-9]+") >= 0 and userDefined = false
      order by name)";

      auto rst = this -> conn_.run(sql);
      dolphindb::VectorSP vp = rst->getColumn(0);
      for(int i = 0; i < vp ->size(); ++i){
            words.emplace_back(vp->getString(i));
      }
};

}