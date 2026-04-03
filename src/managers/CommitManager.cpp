#include "../include/manager.h"
#include <iostream>

using namespace std;

void CommitManager::commit(deque<string> flags, deque<string> args){
    cout << "Commit" << endl;
}

void CommitManager::push(deque<string> flags, deque<string> args){
    cout << "Push" << endl;
}

void CommitManager::pull(deque<string> flags, deque<string> args){  
    cout << "pull" << endl;
}