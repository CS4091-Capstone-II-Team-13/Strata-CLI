/*
 *
 *   Purpose: This file just holds utility functions and debug functions which
 *            have no internal dependencies to this project
 *
 */

#pragma once

#include <filesystem>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

namespace fs = std::filesystem;

using namespace std;

template <typename T> void print_items(T cntr) {
    for (string item : cntr) {
        cout << item << endl;
    }
}

// looks upwards until it finds the .strata directory
inline fs::path find_repository_root(fs::path start_path = fs::current_path()) {
    start_path = fs::absolute(start_path);

    // until we reach the filesystem root, look for the .strata directory
    while (start_path != start_path.root_path()) {
        if (fs::exists(start_path / ".strata")) {
            return start_path;
        }
        start_path = start_path.parent_path();
    }

    // check the last possible path
    if (fs::exists(start_path / ".strata"))
        return start_path;

    return "";
}

inline string glob_to_regex(string glob) {
    string regex_str =
        "^"; // regex requires this at the begining of the expression

    // convert all the glob characters to their regex counterparts
    for (char c : glob) {
        switch (c) {
        case '*':
            regex_str += ".*";
            break;
        case '?':
            regex_str += ".";
            break;
        case '.':
        case '(':
        case ')':
        case '[':
        case ']':
        case '{':
        case '}':
        case '+':
        case '^':
        case '$':
        case '|':
        case '\\':
            // Escape all these special regex characters with a backslash
            regex_str += "\\";
            regex_str += c;
            break;
        default:
            regex_str += c;
            break;
        }
    }

    regex_str += "$"; // regex requires this character at the end
    return regex_str;
}

inline vector<fs::path> scan_repo_files(const fs::path &root,
                                        const string &pattern) {
    vector<fs::path> matches;
    try {
        regex re(glob_to_regex(pattern),
                 regex_constants::icase); // the regex pattern object (checks if
                                          // something matches the pattern)

        // iterate through each file fron root by using
        // recursive_directory_iterator
        for (const auto &entry : fs::recursive_directory_iterator(root)) {

            // Skip the .strata folder and its contents
            auto rel_path = fs::relative(entry.path(), root);
            if (rel_path.string().find(".strata") != string::npos)
                continue;

            // Matched some filename to the pattern
            if (fs::is_regular_file(entry)) {
                if (regex_match(rel_path.string(), re)) {
                    matches.push_back(rel_path);
                }
            }
        }

    } catch (const regex_error &e) {
        cerr << "Invalid pattern: " << e.what() << endl;
        // TODO: just try to find filename that matches the pattern
    }
    return matches;
}
