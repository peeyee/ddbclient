#include "CommandHistory.h"
#include <pwd.h>
#include <unistd.h> 

CommandHistory::CommandHistory()
{
    using namespace std;
    struct passwd *pw = getpwuid(geteuid());
    this -> historyFile = string(pw -> pw_dir) + string("/.cli_history");
    history = new std::deque<string>();
    this -> fin = new std::fstream(historyFile);
    if(fin->is_open()){
        string command;
        short i = 0;
        while (getline(*fin, command) && i < DEPTH)
        {
            history -> push_back(command);
            i++;
        }        
    }
    fin -> close();
}

CommandHistory::~CommandHistory()
{
}

void CommandHistory::add(std::string command){
    if(history->size() < DEPTH){
        history ->push_front(command);
    }else{
        history -> pop_back();
        history -> push_front(command);
    }
    this -> currentPosition = 0;
}

std::string CommandHistory::getPrev(){
    int preIndex = this -> currentPosition == (DEPTH - 1) ? currentPosition : currentPosition + 1;
    this -> currentPosition = preIndex;
    return history ->at(preIndex);
}

std::string CommandHistory::getNext(){
    int nextIndex = this -> currentPosition == 0 ? 0 : currentPosition - 1;
    this -> currentPosition = nextIndex;
    return history ->at(nextIndex);
}

bool CommandHistory::store(){
    std::ofstream fout(historyFile);
    if(fout.is_open()){
        for(std::deque<std::string>::iterator it = (history->begin()); it != (history->end()); ++it){
           fout << *it << "\n";
        }
        fout.close();
        return true;
    }else{
        return false;
    }
}