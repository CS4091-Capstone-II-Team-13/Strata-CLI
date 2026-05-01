/*
/   Date: 2/16/26
/   Ver:  1.0.0
/
/   Purpose:    This main.cpp file handles all of the high-level application
logic
/
*/

#include <deque>
#include <iostream>
#include <memory>
#include <string>

#include "context.h"
#include "manager.h"
#include "parser.h"
#include "strata-middleware-linux-amd64/stratasdk.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    // package arguments into a queue
    std::deque<std::string> arguments(argv, argv + argc);

    // remove the first argument, because that is the execution path
    arguments.pop_front();

    // parse input arguments
    Parser parser(arguments);

    try {
        parser.parse();
    } catch (const exception &e) {
        cout << "Parse Error: " << e.what() << endl;
        cout << e.what() << endl;
    }

    // package managers into a vector
    std::vector<std::unique_ptr<Manager>> managers;
    managers.emplace_back(
        make_unique<CommandFlagManager>()); // use emplace_back to prevent weird
                                            // pointer problems
    managers.emplace_back(make_unique<FileTrackingManager>());
    managers.emplace_back(make_unique<RepositoryStructureManager>());
    managers.emplace_back(make_unique<ConfigManager>());
    managers.emplace_back(make_unique<CommitManager>());
    managers.emplace_back(make_unique<RepositoryStructureManager>());
    managers.emplace_back(make_unique<HistoryManager>());
    managers.emplace_back(make_unique<ProjectManager>());
    // Add new managers here //

    // create context from parsed data
    Context context(move(managers), parser.flags, parser.command,
                    parser.args); // since these are unique pointers, we must
                                  // use move() to transfer ownership

    // execute
    try {
        context.execute();
    } catch (const exception &e) {
        std::cout << "Context Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
