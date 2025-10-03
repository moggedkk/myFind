#ifndef SEARCHFORFILE_H
#define SEARCHFORFILE_H

#include <filesystem>
#include <iostream>

using namespace std;
using namespace std::filesystem;

class searchForFile{
    public:
        searchForFile() = default;
        ~searchForFile() = default;
        bool equals(string &a, string &b, bool case_sen);
        void printFilePath(string& file_to_search, path& direc, bool recursive, bool case_sen);
};

#endif // SEARCHFORFILE_H
