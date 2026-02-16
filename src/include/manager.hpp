#pragma once

#include <vector>

// @breif The purpose of this class is to act as an abstract class for
//        other managers to be derived from.
//        Derived managers should implement relevent functions and the doCommand() function
class Manager {
    public:
        void doCommand();
};