/*
/   Date: 2/16/26
/   Ver:  1.0.0
/
/   Purpose:    This main.cpp file handles all of the high-level application logic
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

