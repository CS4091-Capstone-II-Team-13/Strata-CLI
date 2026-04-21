/*
*
*   Purpose: The Repository acts as a layer between the database and the command functions. 
*
*/

#pragma once

#include <string>
#include <sqlite3.h>
#include <vector>

using namespace std;

class Repository {
    public:
        static Repository& getInstance();
        
        // Initialize the DB file in .strata/
        bool init(const string& projectRoot);

        // repo config
        bool setConfig(const string& key, const string& value);
        string getConfig(const string& key);

        // file staging
        bool stageFile(const string& path, const string& hash, uintmax_t size);
        bool unstageFile(string filePath);
        vector<string> getStagedFiles();
    

    private:
        Repository();
        ~Repository() {
            if (db) {
                sqlite3_close(db);
                db = nullptr;
            }
        }

        sqlite3* db;
        bool initTables();
};