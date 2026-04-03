#include "../include/manager.h"
#include <iostream>

using namespace std;

void CommandFlagManager::help(deque<string> flags, deque<string> args) {
    cout << "HELP" << endl;
}

void CommandFlagManager::version(deque<string> flags, deque<string> args) {
    cout << "VERSION" << endl;
}