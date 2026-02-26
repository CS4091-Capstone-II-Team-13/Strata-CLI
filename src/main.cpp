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
    } catch (const char* msg) {
        cout << msg << endl;
    }
    


    print_items(parser.flags);

    

    return 1;
}

