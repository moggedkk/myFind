#ifndef SEARCHFORFILE_H
#define SEARCHFORFILE_H

#include <filesystem>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
using namespace std::filesystem;

class searchForFile{
    public:
        searchForFile();
        ~searchForFile();

        bool equals(string &a, string &b,
                    bool case_sen);
        void printFilePath(string& file_to_search,
                            path& direc,
                           bool recursive,
                           bool case_sen);

};

#endif // SEARCHFORFILE_H
