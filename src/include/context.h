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
        Context(vector<unique_ptr<Manager>> managers) 
        : managers(move(managers)) {}

        // @brief finds and executes the relevent function for the current context
        void execute();

    private:
        vector<unique_ptr<Manager>> managers;
        deque<string> flags;
        string command;
        deque<string> args;

        // @brief finds the correct manager for the current context
        unique_ptr<Manager> find_manager();
};

