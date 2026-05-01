#include "json.hpp"
#include "manager.h"
#include "repository.h"
#include "strata-middleware-linux-amd64/stratasdk.h"
#include <iostream>

using namespace std;
using json = nlohmann::json;

void ProjectManager::create(deque<string> flags, deque<string> args) {
    if (args.size() != 2) {
        cerr << "Usage: strata create <name> <description>" << endl;
        return;
    }

    strata::Client *client = Repository::getInstance().getClient();
    cout << client->projectCreate(args[0], args[1]);
}

void ProjectManager::projects(deque<string> flags, deque<string> args) {
    strata::Client *client = Repository::getInstance().getClient();
    cout << client->projectList();
}

void ProjectManager::delete_project(deque<string> flags, deque<string> args) {
    if (args.size() != 1) {
        cerr << "Usage: strata delete-project <name>" << endl;
        return;
    }
    strata::Client *client = Repository::getInstance().getClient();
    json list = json::parse(client->projectList());
    for (auto &[_, project] : list.items()) {
        if (project["name"] == args[0]) {
            cout << client->projectDelete(project["id"]) << endl;
            return;
        }
    }
    cout << "Cannot find project with specified name." << endl;
}
