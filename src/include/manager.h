#pragma once

#include <deque>
#include <string>
#include <unordered_map>
#include <functional>
#include <set>

using namespace std;

// @brief The purpose of this class is to act as an abstract class for
//        other managers to be derived from.
//        Derived managers should implement relevent functions
class Manager {
    public:
        virtual unordered_map<string, function<void()>> get_actions() = 0;
        virtual set<string> get_triggers() = 0;
};

// @brief Implements all commands relevent to flags
//        EX: "-h" "-v"
class CommandFlagManager : public Manager {
    public:
        unordered_map<string, function<void()>> get_actions() override {
            return Actions;
        }

        set<string> get_triggers() override {
            return triggers;
        }

        void help();
        void version();

    private: 
        string flag;
        unordered_map<string, function<void()>> Actions = {     // need to bind the functions to this class by doing [this](){}
            {"--help", [this]() { help(); }},
            {"-h", [this]() { help(); }},
            {"--version", [this]() { version(); }},
            {"-v", [this]() { version(); }},
        };

        // @brief the purpose of this set of triggers is to trigger the correct manager, searching a set is much faster than searching the unordered_map
        set<string> triggers = {
            "--help", "-h",
            "--version", "-v"
        };
};