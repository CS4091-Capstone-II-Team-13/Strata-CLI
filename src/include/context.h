/*
*
*   Purpose: Holds the context, which manages all input context related actions (taking parsed input and choosing the correct actions)
*
*/
#pragma once

#include <deque>
#include <string>
#include <vector>
#include <memory>
#include "manager.h"

using namespace std;

class Context {
    public:
        // passes managers into the managers vector
        Context(vector<unique_ptr<Manager>> managers, deque<string> flags, string command, deque<string> args) 
        : managers(move(managers)), flags(move(flags)), command(move(command)), args(move(args)) {}

        // @brief finds and executes the relevent function for the current context
        void execute();

    private:
        vector<unique_ptr<Manager>> managers;
        deque<string> flags;
        string command;
        deque<string> args;
};

