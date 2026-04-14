#include "include/repository.h"
#include "include/queries.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
namespace fs = filesystem;
namespace query = Queries;

Repository& Repository::getInstance() {
    static Repository instance;
    return instance;
}

// use canonical path for initializing the database
bool Repository::init(const string& projectRoot) {
    try {
        // paths
        fs::path rootPath = fs::absolute(projectRoot);
        fs::path strataPath = rootPath / ".strata";
        fs::path dbFilePath = strataPath / "strata.db";

        // Create the .strata directory if it doesn't exist
        if (!fs::exists(strataPath)) {
            if (!fs::create_directories(strataPath)) {
                cerr << "Repository Error: Failed to create directory " << strataPath << endl;
                return false;
            }
        }

        // Open the database using the absolute path string
        // sqlite3_open will create the file if it is missing
        int exit = sqlite3_open(dbFilePath.string().c_str(), &db);

        if (exit != SQLITE_OK) {
            cerr << "Repository Error: Could not open repository database: " << sqlite3_errmsg(db) << endl;
            return false;
        }

        // Enable Foreign Keys for this session
        sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);

        // Initialize the schema
        if (!initTables()) {
            cerr << "Repository Error: Failed to initialize database tables." << endl;
            sqlite3_close(db);
            return false;
        }
        
        return true;

    } catch (const fs::filesystem_error& e) {
        cerr << "Filesystem Error: " << e.what() << endl;
        return false;
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return false;
    }
}

bool Repository::initTables() {
    char* zErrMsg = nullptr;

    int rc = sqlite3_exec(db, query::SQL_SCHEMA_INIT.c_str(), nullptr, nullptr, &zErrMsg);

    if (rc != SQLITE_OK) {
        cerr << "SQL Initialization Error: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
        return false;
    }

    return true;
}