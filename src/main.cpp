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
#include <vector>
#include <deque>

#include "include/parser.h"
#include "include/utils.h"

using namespace std;

int main(int argc, char *argv[]){

    // package arguments into a queue
    deque<string> arguments(argv, argv + argc);

    // parse input arguments
    Parser parser(arguments);

    try{
        parser.parse();
    } catch (const char* msg) {
        cout << msg << endl;
    }


    

    return 1;
}

