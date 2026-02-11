/*
/   Date: 2/11/26
/   Ver:  1.0.0
/
/   Purpose:    This main.cpp file handles all of the std input and output of the command line interface.
/               All commands and flags will be handled in their respective header/src files.
/               
*/

#include <iostream>
#include <string>

#include "fileTracking.hpp"
#include "command.hpp"
#include "flags.hpp"

using namespace std;

// create instance of flag state singleton
FlagState flags;

int main(int argc, char *argv[]){

    // iterate through arguments, modifying behavior for each flag
    for(int i = 0; i < argc; i++) {
        string argument = argv[i];
        if( argument[0] == '-' ) {
            cout << "Flag" << endl;
        }
    }
    

    return 1;
}

