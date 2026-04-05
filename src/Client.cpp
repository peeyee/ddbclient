#include <string>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "DolphinDB.h"
#include "Types.h"
#include "Client.h"
#include "TerminalUtil.h"
namespace cli{
      using namespace std;

      std::string toString(dolphindb::ConstantSP result) {
          if (result->isNull()) {
              return "NULL";
          }

          if (result->isTable()) {
              dolphindb::TableSP table = result;
              int rows = table->size();
              int cols = table->columns();
              int maxRows = 1000;
              int printRows = std::min(rows, maxRows);
              std::ostringstream oss;

              int termWidth = getTermWidth();
              int totalCols = cols;
              int availableWidth = termWidth - 5 - (totalCols * 3);
              if (availableWidth < 10) {
                  availableWidth = 10;
              }

              std::vector<int> colWidths(cols);
              int totalActualWidth = 0;
              for (int c = 0; c < cols; ++c) {
                  std::string header = table->getColumnName(c);
                  int maxLen = static_cast<int>(header.length());
                  for (int r = 0; r < printRows; ++r) {
                      dolphindb::ConstantSP cell = table->getColumn(c)->get(r);
                      std::string cellStr = cell->getString();
                      maxLen = std::max<int>(maxLen, static_cast<int>(cellStr.length()));
                  }
                  colWidths[c] = maxLen;
                  totalActualWidth += maxLen;
              }

              int maxDataWidth = std::max(totalActualWidth, totalCols * 5);
              if (maxDataWidth > availableWidth) {
                  int avgWidth = availableWidth / totalCols;
                  for (int c = 0; c < cols; ++c) {
                      colWidths[c] = std::max(5, std::min(colWidths[c], avgWidth));
                  }
              }

              if (availableWidth / totalCols < 5) {
                  oss << "[Warning] Terminal too narrow to display " << totalCols
                      << " columns horizontally. \n"
                      << "Please use '\\G' (vertical display) at the end of your query, "
                      << "or resize your terminal / use '\\w 300'.\n";
                  return oss.str();
              }

              for (int c = 0; c < cols; ++c) {
                  std::string name = table->getColumnName(c);
                  int width = colWidths[c];
                  if ((int)name.length() > width) {
                      name = name.substr(0, width - 3) + "...";
                  }
                  oss << std::setw(width) << name << " | ";
              }
              oss << "\n";

              for (int c = 0; c < cols; ++c) {
                  int width = colWidths[c];
                  oss << std::setw(width) << std::string(width, '-') << " | ";
              }
              oss << "\n";

              for (int r = 0; r < printRows; ++r) {
                  for (int c = 0; c < cols; ++c) {
                      dolphindb::ConstantSP cell = table->getColumn(c)->get(r);
                      std::string cellStr = cell->getString();
                      int width = colWidths[c];
                      if ((int)cellStr.length() > width) {
                          cellStr = cellStr.substr(0, width - 3) + "...";
                      }
                      oss << std::setw(width) << cellStr << " | ";
                  }
                  oss << "\n";
              }

              if (rows > maxRows) {
                  oss << "(" << rows << " rows total, only first " << maxRows << " displayed)\n";
              }
              return oss.str();
          }

          return result->getString();
      }

      bool Client::connect(string host, int port, string username, string password){
            bool isConnect = this -> conn_.connect(host, port, username, password);
            this -> connected_ = isConnect;
            return isConnect;
      }

      void Client::runInteractive(string cmd){
            auto start = std::chrono::high_resolution_clock::now();  
            dolphindb::ConstantSP result =  this -> conn_.run(cmd);
            string fmtResult = toString(result);
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
            where strlen(name) >= 3 and regexFind(name, "^[a-zA-Z0-9]+") >= 0
            order by name)";

            auto rst = this -> conn_.run(sql);
            dolphindb::VectorSP vp = rst->getColumn(0);
            for(int i = 0; i < vp ->size(); ++i){
                  words.emplace_back(vp->getString(i));
            }
      };

      int Client::runShell(const std::string& cmd){
            int errcode = std::system(cmd.c_str());
            return errcode;
      }

}