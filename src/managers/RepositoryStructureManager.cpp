#include "manager.h"
#include "repository.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

using namespace std;

void RepositoryStructureManager::merge(deque<string> flags,
                                       deque<string> args) {}

void RepositoryStructureManager::rebase(deque<string> flags,
                                        deque<string> args) {}

void RepositoryStructureManager::branch(deque<string> flags,
                                        deque<string> args) {}

void RepositoryStructureManager::stash(deque<string> flags,
                                       deque<string> args) {}

void RepositoryStructureManager::init(deque<string> flags, deque<string> args) {
    Repository &repo = Repository::getInstance();

    string projectRoot = fs::current_path();
    repo.init(projectRoot);
}
