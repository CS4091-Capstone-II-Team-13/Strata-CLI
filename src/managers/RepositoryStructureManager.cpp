#include "../include/manager.h"
#include "../include/repository.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

void RepositoryStructureManager::merge(deque<string> flags, deque<string> args){
    
}

void RepositoryStructureManager::rebase(deque<string> flags, deque<string> args){

}

void RepositoryStructureManager::branch(deque<string> flags, deque<string> args){

}

void RepositoryStructureManager::stash(deque<string> flags, deque<string> args){

}

void RepositoryStructureManager::init(deque<string> flags, deque<string> args) {
    RepositoryManager& repoMan = RepositoryManager::getInstance();

    string projectRoot = fs::current_path();
    repoMan.init(projectRoot);

}