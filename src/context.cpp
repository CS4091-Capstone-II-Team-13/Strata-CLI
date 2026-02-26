#include "include/context.h"

using namespace std;

void Context::execute() {
    
    // iterate through all of the managers
    for(int i = 0; i < managers.size(); i++) {

        // get the triggers and actions
        auto triggers = managers[i]->get_triggers();
        auto actions = managers[i]->get_actions();

        // iterate through flags first
        for(auto& flag : flags) {

            auto triggerIt = triggers.find(flag);
            if (triggerIt != triggers.end()) {
                // execute (assumes that the triggers are implemented)
                auto actionIt = actions.find(flag);
                actionIt->second();
            }
        }

        // otherwise try to find the command
        auto it = triggers.find(command);
        if(it != triggers.end()) {
            // execute (assumes that the triggers are implemented)
            auto actionIt = actions.find(command);
            actionIt->second();
        }

    }
}