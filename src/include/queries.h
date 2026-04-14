/*
*
*   Purpose: A namespace which holds all standard const queries that are exclusively used by the RepositoryManager
*
*/

#pragma once

#include <string>

using namespace std;

namespace Queries {
    const string SQL_SCHEMA_INIT = R"(
        CREATE TABLE IF NOT EXISTS config (
            key   TEXT PRIMARY KEY, 
            value TEXT
        );

        CREATE TABLE IF NOT EXISTS session (
            user_id       TEXT PRIMARY KEY, 
            username      TEXT, 
            access_token  TEXT, 
            refresh_token TEXT, 
            expires_at    INTEGER
        );

        CREATE TABLE IF NOT EXISTS chunk (
            hash         TEXT PRIMARY KEY, -- holds the path to the file
            size_bytes   INTEGER NOT NULL,
            ref_count    INTEGER DEFAULT 0,
            created_at   DATETIME DEFAULT CURRENT_TIMESTAMP
        );

        CREATE TABLE IF NOT EXISTS commits (
            id          TEXT PRIMARY KEY,
            project_id  TEXT NOT NULL,
            author_id   TEXT NOT NULL,
            parent_id   TEXT,             -- backwards compat (may be removed depending on the API)
            parent_ids  TEXT NOT NULL,    -- JSON array of strings
            message     TEXT NOT NULL,
            created_at  DATETIME DEFAULT CURRENT_TIMESTAMP
        );

        CREATE TABLE IF NOT EXISTS file_entries (
            id           TEXT PRIMARY KEY,
            file_id      TEXT NOT NULL,
            path         TEXT NOT NULL,    -- Relative path in repo
            commit_id    TEXT NOT NULL,
            total_size   INTEGER NOT NULL,
            chunk_hashes TEXT NOT NULL,
            created_at   DATETIME DEFAULT CURRENT_TIMESTAMP,
            
            FOREIGN KEY (commit_id) REFERENCES commits(id)
        );

        CREATE TABLE IF NOT EXISTS staging (
            path         TEXT PRIMARY KEY, 
            hash         TEXT NOT NULL,     -- The 'root' hash or tree hash
            size_bytes   INTEGER NOT NULL,
            last_modified INTEGER
        );

        -- Indexes for fast lookup
        CREATE INDEX IF NOT EXISTS idx_file_path ON file_entries(path);
        CREATE INDEX IF NOT EXISTS idx_file_commit ON file_entries(commit_id);
        CREATE INDEX IF NOT EXISTS idx_commit_project ON commits(project_id);
    )";

    // Config Queries

    
}