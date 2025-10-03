#include "searchForFile.h"

#include <iostream>
#include <unistd.h>
#include <cctype>
#include <algorithm>
#include <filesystem>

using namespace std;
using namespace std::filesystem;


searchForFile::searchForFile() {}

searchForFile::~searchForFile() {}

bool searchForFile::equals( string &a,  string &b, bool case_sen){
    if (!case_sen){ return a == b; }
    if (a.size() != b.size()){ return false; }
    for (size_t i = 0; i < a.size(); ++i) {
        unsigned char ca = static_cast<unsigned char>(a[i]);
        unsigned char cb = static_cast<unsigned char>(b[i]);
        if (std::tolower(ca) != std::tolower(cb)){ return false;}
    return true;
    }
}

void searchForFile::printFilePath(string &file_to_search, path &direc, bool recursive, bool case_sen){
    try{
            if(recursive){
                for (const auto &entry : recursive_directory_iterator(direc)) {
                    string entry_name = entry.path().filename().string();
                    if (equals(entry_name, file_to_search, case_sen)) {
                        cout << getpid() << ": "<< file_to_search << ": " << absolute(entry.path().lexically_normal()) << endl;
                    }
                }
            }else{
                for(const auto &entry: directory_iterator(direc)){
                    string entry_name = entry.path().filename().string();
                    if (equals(entry_name, file_to_search, case_sen)) {
                        cout << getpid() << ": " << file_to_search << ": " << absolute(entry.path().lexically_normal()) << endl;
                    }
                }
        }
    }catch (const filesystem_error& e) {
            cerr << "filesystem error: " << e.what() << '\n';
    }
}

