#include "manager.h"
#include "repository.h"

#include <iostream>

using namespace std;

void ConfigManager::config(deque<string> flags, deque<string> args) {
    if (flags.size() <= 0) {
        cout << "Error: No config flag" << endl;
    }

    if (args.size() <= 0) {
        cout << "Error: No config argument" << endl;
        return;
    }

    for (auto &flag : flags) {
        if (flag == "--remote") {
            remote(args[0]);
        } else if (flag == "--email") {
            email(args[0]);
        } else if (flag == "--password") {
            password(args[0]);
        } else if (flag == "--username") {
            username(args[0]);
        }
    }
}

// TODO: add guide printouts that tell the user how to use config on errors
// above

void ConfigManager::remote(string remote) {
    Repository::getInstance().setConfig("remote", remote);
}

void ConfigManager::email(string email) {
    Repository::getInstance().setConfig("email", email);
}

void ConfigManager::password(string password) {
    Repository::getInstance().setConfig("password", password);
}

void ConfigManager::username(string username) {
    Repository::getInstance().setConfig("username", username);
}
