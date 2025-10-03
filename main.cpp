#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>

#include "searchForFile.h"

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
        pid_t pid = fork();                               // forking child prozess
        if(pid == 0){                                     // forking successful
            string file_to_search = filenames[i];         // file to look for
            finder.printFilePath(file_to_search, direc,
                        recursive, case_sen);             //looking for file in given direc
            _exit(0);
        }
        while (wait(nullptr) > 0){}                       //Zombie-prevention. "parent process" waits untill all children are finished
    }

    return 0;
}

void getParameters(bool &recursive, bool &case_sen, string &text_direc, vector<string> &filenames, int argc, char* argv[]){

        int opt;
        //Get all given arguments
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
            text_direc = argv[optind];
            for (int i = optind+1; i < argc; i++) {
                filenames.push_back(argv[i]);
            }
        }
}
