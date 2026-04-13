/*
*
*   Purpose: Only holds the Parser class
*
*/
#pragma once

#include <string>
#include <deque> 
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
        deque<string> flags;
        string command;
        deque<string> args; // all remaining inputs will end up as args

        // main entry point, will throw errors to be caught outside of the scope of Parser
        void parse();

    private:
        bool parseFlag();
        void parseCommand();

        // TODO: implement a method to modify/add these sets because its duplicating code in manager.h

        // matches to these 2 sets for commands and flags
        set<string> commandSet = {
            "add", "restore", "pull", "push", "commit", "push", "pull",
            "merge", "rebase", "branch", "stash", "config", "init"
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