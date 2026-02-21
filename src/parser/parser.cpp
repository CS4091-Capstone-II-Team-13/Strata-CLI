#include "../include/parser.h"

using namespace std;

void Parser::parse() {
    if (!parseFlag()) return;
    
    parseCommand();
    parseFlag();

    // the remainder of the arguments will be passed forward
    args = deque<string>(inputs);
}

// @brief parses a flag token
// @return true: flag requires other arguments
// @return false: flag doesn't require other arguments
bool Parser::parseFlag() {
    if (inputs[0][0] == '-') {
        flags.push_back(inputs[0]);

        if (commandFlagSet.find(inputs[0]) != commandFlagSet.end()){
            return false;
        }

        inputs.pop_front();
        parseFlag();
        return true;
    }
}

void Parser::parseCommand() {
    if(commandSet.find(inputs[0]) != commandSet.end()) {
        command = inputs[0];
        inputs.pop_front();
        return;
    } else {
        throw ("Incorrect Command Argument: " + inputs[0]);
    }
}