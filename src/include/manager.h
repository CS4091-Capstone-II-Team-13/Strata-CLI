#pragma once

#include <deque>
#include <string>
#include <unordered_map>
#include <functional>
#include <set>

using namespace std;

// @brief The purpose of this class is to act as an abstract class for
//        other managers to be derived from.
//        Derived managers should implement relevent functions, actions, and triggers
//        
// NOTE:  All implemented functions must accept arguments in the form of (deque<string> flags, deque<string> args)
class Manager {
    public:
        virtual ~Manager() = default;

        virtual unordered_map<string, function<void(deque<string>, deque<string>)>> get_actions() {
            return Actions;
        }

        virtual set<string> get_triggers() {
            return triggers;
        }

    protected: 
        // This unordered_map simply maps triggers to actions, so that the context can grab the right function
        unordered_map<string, function<void(deque<string>, deque<string>)>> Actions;

        // the purpose of this set of triggers is to trigger the correct manager, searching a set is much faster than searching the unordered_map
        set<string> triggers = {};  
};

// @brief Implements all commands relevent to flags
//        EX: "-h" "-v"
class CommandFlagManager : public Manager {
    public:
        CommandFlagManager() {
            Actions = { // need to bind the functions to this class by doing [this](){}
                {"--help",    [this](auto f, auto a) { help(f, a); }},
                {"-h",        [this](auto f, auto a) { help(f, a); }},
                {"--version", [this](auto f, auto a) { version(f, a); }},
                {"-v",        [this](auto f, auto a) { version(f, a); }}
            };

            triggers = {"--help", "-h", "--version", "-v"};
        }

        void help(deque<string> flags, deque<string> args);
        void version(deque<string> flags, deque<string> args);
};

class FileTrackingManager : public Manager {
    public:
        FileTrackingManager() {
            Actions = {
                {"add",    [this](auto f, auto a) { add(f, a); }},
                {"restore",    [this](auto f, auto a) { restore(f, a); }},
                {"status",    [this](auto f, auto a) { status(f, a); }},
            };
            triggers = {"add", "restore", "status"};
        }

        void add(deque<string> flags, deque<string> args);
        void restore(deque<string> flags, deque<string> args);
        void status(deque<string> flags, deque<string> args);
};

class ConfigManager : public Manager {
    public:
        ConfigManager() {
            Actions = {
                {"config",    [this](auto f, auto a) { config(f, a); }},
            };
            triggers = {"config"};
        }

        void config(deque<string> flags, deque<string> args);

        void email(string email);
        void password(string pass);
        void username(string username);
};

// Handles all commit commands like: "commit", "push", "pull"
class CommitManager : public Manager {
    public:
        CommitManager() {
            Actions = {};
            triggers = {"commit", "push", "pull"};
        }

        void commit(deque<string> flags, deque<string> args);
        void push(deque<string> flags, deque<string> args);
        void pull(deque<string> flags, deque<string> args);
};

// Handles any command relevent to the structure of the repository: "merge", "rebase", "branch", "stash"
class RepositoryStructureManager : public Manager {
    public:
        RepositoryStructureManager() {
            Actions = {};
            triggers = {"merge", "rebase", "branch", "stash"};
        }

        void merge(deque<string> flags, deque<string> args);
        void rebase(deque<string> flags, deque<string> args);
        void branch(deque<string> flags, deque<string> args);
        void stash(deque<string> flags, deque<string> args);
};

// Handles all the "history" commands relevent to the history endpoints in the server api
class HistoryManager : public Manager {
    public:
        HistoryManager() {
            Actions = {};
            triggers = {};
        }
};

// Handles all "project" commands relevent to the history endpoints in the server api "POST/GET/DELETE /projects"
class ProjectManager : public Manager {
    public:
        ProjectManager() {
            Actions = {};
            triggers = {"create", "projects", "delete-project"};
        }
        
        void create(deque<string> flags, deque<string> args);
        void projects(deque<string> flags, deque<string> args);
        void delete_project(deque<string> flags, deque<string> args);

};