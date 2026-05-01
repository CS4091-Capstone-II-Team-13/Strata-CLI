#include "include/context.h"
#include <stdexcept>

using namespace std;

void Context::execute() {

    // iterate through all of the managers
    for (int i = 0; i < int(managers.size()); i++) {

        // get the triggers and actions
        auto triggers = managers[i]->get_triggers();
        auto actions = managers[i]->get_actions();

        // iterate through flags first
        for (auto &flag : flags) {

            auto triggerIt = triggers.find(flag);
            if (triggerIt != triggers.end()) {

                auto actionIt = actions.find(flag);
                if (actionIt != actions.end()) {
                    actionIt->second(flags, args);
                } else {
                    throw runtime_error("Flag: " + flag +
                                        ", is not implemented yet");
                }
            }
        }

        // otherwise try to find the command
        auto it = triggers.find(command);
        if (it != triggers.end()) {

            auto actionIt = actions.find(command);
            if (actionIt != actions.end()) {
                actionIt->second(flags, args);
            } else {
                throw runtime_error("Command: " + command +
                                    ", is not implemented yet");
            }
        }
    }
}
