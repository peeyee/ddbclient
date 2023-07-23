#include <iostream>
#include <fstream>  
#include "FileReader.h"

std::string FileReader::read(std::string filename){
    std::ifstream fin(filename);
    if(fin.is_open()){
        std::string line;
        while (std::getline(fin, line))
        {
            content_ += line + "\n";
        }
        fin.close();
    }else{
        std::cout << "Failed to open " << filename << ", please check if it exists or you have the right to read it."<< std::endl;
    }
    return content_;
};