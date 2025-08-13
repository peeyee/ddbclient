#include <string>

namespace cli{
    using std::string;

    class  StringUtil{
    
        public:
            static bool endsWith(const string& str, const string& suffix);
            static bool contains(const string& str, const string& substr);
    };

}