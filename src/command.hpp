#ifndef COMMAND_HPP
#define COMMAND_HPP

// @brief using this type def to can pass function pointers
typedef int (*function_pointer)();

function_pointer getCommandFunction(string command);

#endif