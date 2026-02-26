#pragma once

#include <deque>
#include <string>

using namespace std;

// @brief The purpose of this class is to act as an abstract class for
//        other managers to be derived from.
//        Derived managers should implement relevent functions
class Manager {
    public:
};

// @brief Implements all commands relevent to flags
//        EX: "-h" "-v"
class CommandFlagManager : public Manager {
    public:
        void help();
        void version();

    private: 
        string flag;
};