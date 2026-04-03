/*
/   Date: 2/16/26
/   Ver:  1.0.0
/
/   Purpose:    This main.cpp file handles all of the high-level application logic
/               
*/

#include <iostream>
#include <string>
#include <deque>
#include <memory>

#include "include/parser.h"
#include "include/utils.h"
#include "include/manager.h"
#include "include/context.h"

using namespace std;

int main(int argc, char *argv[]){

    // package arguments into a queue
    deque<string> arguments(argv, argv + argc);

    // remove the first argument, because that is the execution path
    arguments.pop_front();

    // parse input arguments
    Parser parser(arguments);

    try{
        parser.parse();
    } catch (const exception& e) {
        cout << "Parse Error: " << endl;
        cout << e.what() << endl;
    }
    
    // package managers into a vector
    vector<unique_ptr<Manager>> managers;
    managers.emplace_back(make_unique<CommandFlagManager>());   // use emplace_back to prevent weird pointer problems
    managers.emplace_back(make_unique<FileTrackingManager>());

    managers.emplace_back(make_unique<ConfigManager>());
    // Add new managers here //

    // create context from parsed data
    Context context(move(managers), parser.flags, parser.command, parser.args);    // since these are unique pointers, we must use move() to transfer ownership

    // execute
    try {
        context.execute();
    } catch (const exception& e) {
        cout << "Context Erorr: " << endl;
        cout << e.what() << endl;
    }

    return 1;
}

