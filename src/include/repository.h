/*
*
*   Purpose: The RepositoryManager acts as a layer between the database and the command functions. 
*
*/

#pragma once

#include <string>
#include <sqlite3.h>
#include <vector>

using namespace std;

class RepositoryManager {
    public:
    static RepositoryManager& getInstance();
    
    // Initialize the DB file in .strata/
    bool init(const string& projectRoot);
    
    // Generic execution for INSERT/UPDATE
    bool execute(const string& sql);

    bool setConfig(const string& key, const string& value);
    string getConfig(const string& key);

    bool storeBlob(const string& hash, const vector<char>& data);

private:
    RepositoryManager() : db(nullptr) {}
    sqlite3* db;

    bool initTables();
};