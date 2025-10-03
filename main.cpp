#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>

#include "include/searchForFile.h"

using namespace std;
using namespace std::filesystem;

void getParameters(bool &recursive, bool &case_sen, string &text_direc, vector<string> &filenames, int, char*[]);

/*
  Program behavior:

  - The program parses options with getopt():
      -R  enables recursive search
      -i  enables case-sensitive matching
      <dir> search root directory
      <file1> <file2> ... target file names
  - For each filename, the parent process calls fork().
    Each child searches independently by calling finder.printFilePath().
  - Children print every match to stdout as a full line containing the absolute path.
    No explicit sorting is applied; lines appear as matches are found.
  - The parent waits for all children (wait loop) to avoid zombies and to ensure
    the program exits only after every search finishes.
*/

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
