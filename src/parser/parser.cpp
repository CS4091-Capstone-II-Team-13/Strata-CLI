#include "../include/parser.h"
#include <set>

using namespace std;

void Parser::parse() {
    parseFlag();
    parseCommand();
    parseFlag();

    // the remainder of the arguments will be passed forward
    args = deque<string>(inputs);
}

void Parser::parseFlag() {
    if (inputs[0][0] == '-') {
        flags.push_back(inputs[0]);
        inputs.pop_front();
        parseFlag();
        return;
    }
}

set<string> commands = {
    "pull",
    "push",
};

void Parser::parseCommand() {
    if(commands.find(inputs[0]) != commands.end()) {
        command = inputs[0];
        inputs.pop_front();
        return;
    } else {
        throw ("Incorrect Command Argument: " + inputs[0]);
    }
}