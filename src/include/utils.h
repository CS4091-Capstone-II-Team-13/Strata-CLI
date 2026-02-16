/*
*
*   Purpose: This file just holds utility functions and debug functions which
*            have no internal dependencies to this project
*
*/

#pragma once

#include <string>
#include <iostream>

using namespace std;

template <typename T>
void print_items(T cntr) {
    for (string item : cntr) {
        cout << item << endl;
    }
}