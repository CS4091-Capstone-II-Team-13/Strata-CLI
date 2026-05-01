#include "../include/manager.h"
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
        if (flag == "--email") {
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

void ConfigManager::email(string email) { cout << "Changing Email" << endl; }

void ConfigManager::password(string pass) {
    cout << "Changing Password" << endl;
}

void ConfigManager::username(string username) {
    cout << "Changing username" << endl;
}
