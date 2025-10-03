#include <iostream>
#include <cctype>
#include <algorithm>
#include <filesystem>
#include <unistd.h>

#include "../include/searchForFile.h"

using namespace std;
using namespace std::filesystem;


bool searchForFile::equals( string &a,  string &b, bool case_sen){
    //Compare filenames and lower the string if case sensitive
    if (!case_sen){ return a == b; }
    if (a.size() != b.size()){ return false; }
    //filnames to lower to compare
    for (size_t i = 0; i < a.size(); ++i) {
        unsigned char ca = static_cast<unsigned char>(a[i]);
        unsigned char cb = static_cast<unsigned char>(b[i]);
        if (tolower(ca) != tolower(cb)){ return false;}
    }
    return true;
}

void searchForFile::printFilePath(string &file_to_search, path &direc, bool recursive, bool case_sen){
    try{
            if(recursive){
                //Search recursivly in directory and subdirectory
                for (const auto &entry : recursive_directory_iterator(direc)) {
                    string entry_name = entry.path().filename().string();
                    if (equals(entry_name, file_to_search, case_sen)) {
                        cout << getpid() << ": "<< file_to_search << ": " << absolute(entry.path().lexically_normal()) << endl;
                    }
                }
            }else{
                //Only look in current direc and not in sub direc
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

