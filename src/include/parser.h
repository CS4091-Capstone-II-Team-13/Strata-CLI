#pragma once

#include <string>
#include <deque> 
#include <vector>

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
        void parseFlag();
        void parseCommand();
};