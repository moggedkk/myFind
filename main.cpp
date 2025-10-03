#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>

#include "include/searchForFile.h"

using namespace std;
using namespace std::filesystem;

void getParameters(bool &recursive, bool &case_sen, string &text_direc, vector<string> &filenames, int, char*[]);

int main(int argc, char* argv[]){
    searchForFile finder;
    bool recursive = false;
    bool case_sen = false;
    string text_direc;
    vector<string> filenames;
    getParameters(recursive, case_sen, text_direc, filenames, argc, argv);
    path direc{text_direc};
    //Fork for every filename:
    for(int i = 0; i < filenames.size(); i++){
        pid_t pid = fork();
        // forking successful
        if(pid == 0){
            // file to look for
            string file_to_search = filenames[i];
            finder.printFilePath(file_to_search, direc,
                        recursive, case_sen);
            _exit(0);
        }
        //Zombie-prevention. "parent process" waits untill all children are finished
        while (wait(nullptr) > 0){}
    }

    return 0;
}

void getParameters(bool &recursive, bool &case_sen, string &text_direc, vector<string> &filenames, int argc, char* argv[]){
        int opt;
        //Get all given arguments from input
        while((opt = getopt(argc, argv, "Ri::")) != -1){
            switch(opt){
                case 'R':
                    recursive = true;
                    break;
                case 'i':
                    case_sen = true;
                    break;
            }
        }
        if(optind < argc){
            //Getting directory as a string
            text_direc = argv[optind];
            //Get all file names as a list
            for (int i = optind+1; i < argc; i++) {
                filenames.push_back(argv[i]);
            }
        }
}
