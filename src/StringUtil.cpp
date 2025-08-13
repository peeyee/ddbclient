#include "StringUtil.h"


namespace cli{

    bool StringUtil::endsWith(const string& str, const string& suffix){
        if (str.size() < suffix.size()) {  
            return false;  
        }  
        return str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;  
    };

    bool StringUtil::contains(const string& str, const string& substr){
        size_t n = str.find(substr);
        return n == string::npos ? false : true;
    }

}

