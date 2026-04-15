#include "include/repository.h"
#include "include/queries.h"
#include "include/utils.h"
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

Repository::Repository() {
    // Locate the repo root
    fs::path root = find_repository_root();
    
    if (root.empty()) {
        db = nullptr; // We aren't inside a repo
        return;
    }

    // Construct the path to the DB file
    fs::path dbPath = root / ".strata" / "strata.db";

    // Open the SQLite connection
    int rc = sqlite3_open(dbPath.c_str(), &db);

    if (rc != SQLITE_OK) {
        std::cerr << "Strata Error: Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        db = nullptr;
    } else {
        // Enable Write-Ahead Logging for better performance
        sqlite3_exec(db, "PRAGMA journal_mode=WAL;", nullptr, nullptr, nullptr);
    }
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

// inserts the path, hash, and size of a file into the staging table
// Returns true if the operation is successfull, returns false otherwise
bool Repository::stageFile(const string& path, const string& hash, uintmax_t size) {
    // create sql statement
    // INSERT OR REPLACE based on path to prevent duplication
    const char* sql = "INSERT OR REPLACE INTO staging (path, hash, size_bytes, last_modified) "
                      "VALUES (?, ?, ?, CURRENT_TIMESTAMP);";
    
    sqlite3_stmt* stmt;
    
    // Prepare the sql statement in the sqlite engine 
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Repository Error: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Bind the C++ variables to the '?' placeholders
    // SQLITE_TRANSIENT prevents going out of scope
    sqlite3_bind_text(stmt, 1, path.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, hash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 3, static_cast<sqlite3_int64>(size));

    // Execute the sql statement
    int rc = sqlite3_step(stmt);

    // Clean up the statement memory
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        cerr << "Repository Error: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    return true;
}