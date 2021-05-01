#pragma once
#include <string>

// From: https://github.com/andrew-hardin/cmake-git-version-tracking

class VersionInfo {
public:

    static std::string version_string();

private:
    // Is the metadata populated? We may not have metadata if
    // there wasn't a .git directory (e.g. downloaded source
    // code without revision history).
    static bool populated();

    // Were there any uncommitted changes that won't be reflected
    // in the CommitID?
    static bool is_dirty();

    static std::string author_name();
    static std::string author_email();
    static std::string commit_SHA1();
    static std::string commit_date();
    static std::string commit_subject();
    static std::string commit_body();
    static std::string describe();
    static std::string branch();
};