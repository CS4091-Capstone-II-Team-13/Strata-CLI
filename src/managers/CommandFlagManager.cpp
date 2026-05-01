#include "manager.h"
#include <iostream>

using namespace std;

void CommandFlagManager::help(deque<string> flags, deque<string> args) {
    cout << R"(
Strata CLI
usage: strata <command> [options]

File Tracking
  add <pattern>
  store
  status

Config
  config --<remote|email|password|username> <value>

Commit
  commit
  push
  pull

Structure
  merge
  rebase
  branch
  stash
  init

Project
  create <name> <description>
  projects
  delete-project <name>
)" << endl;
}

void CommandFlagManager::version(deque<string> flags, deque<string> args) {
    cout << "VERSION" << endl;
}