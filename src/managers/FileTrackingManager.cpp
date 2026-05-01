#include "manager.h"
#include "repository.h"
#include "utils.h"

#include <filesystem>
#include <iostream>
#include <sqlite3.h>

using namespace std;

// finds files matching the pattern in the first argument, and adds them to the
// staging table
void FileTrackingManager::add(deque<string> flags, deque<string> args) {
    if (args.empty()) {
        cerr << "File Tracking Error: No path or pattern specified. Usage: "
                "strata add <pattern>"
             << endl;
        return;
    }

    // used for file staging
    Repository &repo = Repository::getInstance();

    // find repo root
    fs::path repoRoot = find_repository_root();
    if (repoRoot.empty()) {
        cerr << "File Tracking Error: Not a strata repository" << endl;
        return;
    }

    // if the user does . for the pattern change it to the klein star
    string pattern = args[0];
    if (pattern == ".") {
        pattern = '*';
    }

    // scan for matched files
    vector<fs::path> matchedFiles = scan_repo_files(repoRoot, pattern);

    // add each file to the staging table
    for (const auto &relPath : matchedFiles) {
        fs::path fullPath = repoRoot / relPath;

        // Calculate metadata
        string fileHash =
            "abcdefghijklmnop"; // TODO: use the file hashing function found in
                                // the middleware
        uintmax_t fileSize = fs::file_size(fullPath);

        // Database Update
        if (!repo.stageFile(relPath.string(), fileHash, fileSize)) {
            cerr << "Database Error: Failed to stage " << relPath.string()
                 << endl;
        }
    }
}

// Assume that args[0] is a pattern to match to filenames
void FileTrackingManager::restore(deque<string> flags, deque<string> args) {
    Repository &repo = Repository::getInstance();

    // check for invalid arguments
    if (args.empty()) {
        cerr << "No Filepath given" << endl;
        return;
    }

    // set the . to a klein star for pattern matching-
    string pattern = args[0];
    if (pattern == ".") {
        pattern = '*';
    }

    // scan for all files that could match the pattern
    fs::path repoRoot = find_repository_root();
    vector<fs::path> filenames = scan_repo_files(repoRoot, pattern);

    // unstage all of the matches
    for (auto file : filenames) {
        repo.unstageFile(file);
    }
}

void FileTrackingManager::status(deque<string> flags, deque<string> args) {
    fs::path repoRoot = find_repository_root();
    vector<fs::path> filenames = scan_repo_files(repoRoot, "*");
    Repository &repo = Repository::getInstance();

    // print out information about the project (repo info) (branch, name, ...)
    cout << "Project: " << "<Project name>" << endl;
    cout << "Branch: " << "<Branch name>" << endl;

    cout << endl;

    // print out files in staging
    cout << "Changes to be committed:" << endl
         << "\t(use \"strata restore <file>\" to unstage)" << endl;

    vector<string> filePaths = repo.getStagedFiles();
    for (auto file : filePaths) {
        cout << file << endl;
    }

    cout << endl;

    // print out modified files not staged for commit
    cout << "Changes not staged for commit:" << endl;
    cout << "\t(use \"strata add <file>\" to update what will be commited)"
         << endl;
    cout << "\t(use \"strata restore <file>\" to discard changes in working "
            "directory)"
         << endl;

    cout << endl;
}
