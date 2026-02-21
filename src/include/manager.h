#pragma once

#include <deque>
#include <string>

using namespace std;

class CommandFlagManager {
    public:
        void help();
        void version();

    private: 
        string flag;
};