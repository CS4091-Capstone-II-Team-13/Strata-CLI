/*
*
*   Purpose: This file just holds utility functions and debug functions which
*            have no internal dependencies to this project
*
*/

#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <regex>

namespace fs = std::filesystem;

using namespace std;

template <typename T>
void print_items(T cntr) {
    for (string item : cntr) {
        cout << item << endl;
    }
}

// looks upwards until it finds the .strata directory
fs::path find_repository_root(fs::path start_path = fs::current_path()) {
    start_path = fs::absolute(start_path);
    
    // until we reach the filesystem root, look for the .strata directory
    while (start_path != start_path.root_path()) {
        if (fs::exists(start_path / ".strata")) {
            return start_path;
        }
        start_path = start_path.parent_path();
    }
    
    if (fs::exists(start_path / ".strata")) return start_path; // check the last possible path

    return "";
}

string glob_to_regex(string glob) {
    // replace special regex characters
    static const regex specialChars(R"([-[\]{}()+.,^$|#\s])");
    glob = regex_replace(glob, specialChars, R"(\$&)");

    // Convert glob wildcards to regex equivalents
    glob = regex_replace(glob, regex(R"(\\\*)"), ".*");
    glob = regex_replace(glob, regex(R"(\\\?)"), ".");
    
    return "^" + glob + "$"; // Match whole string
}

vector<fs::path> scan_repo_files(const fs::path& root, const string& pattern) {
    vector<fs::path> matches;
    try {
        regex re(glob_to_regex(pattern), regex_constants::icase); // the regex pattern object (checks if something matches the pattern)

        for (const auto& entry : fs::recursive_directory_iterator(root)) {

            // Skip the .strata folder and its contents
            auto rel_path = fs::relative(entry.path(), root);
            if (rel_path.string().find(".strata") != string::npos) continue;

            if (fs::is_regular_file(entry)) {
                if (regex_match(rel_path.string(), re)) {
                    matches.push_back(rel_path);
                }
            }
        }
    } catch (const regex_error& e) {
        cerr << "Invalid pattern: " << e.what() << endl;
        // TODO: just try to find filename that matches the pattern
    }
    return matches;
}