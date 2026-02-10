/*
/   Date: 2/10/26
/   Ver:  1.0.0
/
/   Purpose:    This command.cpp will handle matching a command to it's relevent function ( acting as a facade between main and the commands )
/               
*/
#include <string>

using namespace std;

// @brief using this type def to can pass function pointers
typedef int (*function_pointer)();

function_pointer getCommandFunction(string command) {



}