#pragma once

#include <deque>
#include <string>
#include <unordered_map>
#include <functional>

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
        unordered_map<string, function<void()>> Actions = {     // be sure to use bind() to bind function pointers with this class
            {"--help", bind(help, this)},
            {"--version", bind(version, this)},
        };

        // @brief sets aliases for every Action
        // ex: -h -> --help
        //     -v -> --version
        unordered_map<string, string> aliases = {
            {"-h", "--help"},
            {"-v", "--version"}
        };
};