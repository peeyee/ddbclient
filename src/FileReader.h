#include <iostream>
namespace cli{
class FileReader{
    public:
        std::string read(std::string filename);
        FileReader(){};
        ~FileReader(){};
    private:
        std::string content_;



};

}