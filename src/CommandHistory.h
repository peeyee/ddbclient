#include <deque>
#include <string>
#include <fstream>

/**
 * 
 *  use deque to store command history;
 *  1. insert at head.
 *  2. delete at tail if it was full.
 *  3. the lastest command is stored at head, the queue is like:
 *  N0100 -> N099 -> ... NO1
 *  where most recently command is NO100
 * 
*/

class CommandHistory
{

private:
    std::deque<std::string> * history;
    std::string historyFile;
    const short DEPTH = 100;
    int currentPosition = 0; 
    std::fstream * fin;


public:
    CommandHistory();
    ~CommandHistory();
    void add(std::string command);
    std::string getPrev();
    std::string getNext();
    bool store();
};


