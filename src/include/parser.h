#pragma once

#include <string>
#include <deque> 
#include <vector>
#include <set>

using namespace std;

// @breif the purpose of this class is to hold the outputs from the parser functions
// @details otherwise 3 objects would need to be passed by reference to the main parse function
class Parser {
    public:
        Parser(deque<string> inputs) : inputs(inputs) {};

        // each item will be removed as it's parsed
        deque<string> inputs;

        // outputs
        vector<string> flags;
        string command;
        deque<string> args; // all remaining inputs will end up as args

        // main entry point, will throw errors to be caught outside of the scope of Parser
        void parse();

    private:
        bool parseFlag();
        void parseCommand();

        // matches to these 2 sets for commands and flags
        set<string> commandSet = {
            "pull", "push",
        };

        set<string> flagSet = {
            "-h", "-H", "--help",
            "-v", "-V", "--version",
        };

        // flags that don't need any other arguments
        set<string> commandFlagSet = {
            "-h", "-H", "--help",
            "-v", "-V", "--version",
        };

};