#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <cctype> //for toupper/tolower
#include <algorithm> //for compare
#include <sys/wait.h>

using namespace std;
using namespace std::filesystem;

void getParameters(bool &recursive, bool &case_sen, string &text_direc, vector<string> &filenames, int, char*[]);
//void splitProcess(pid_t pid, vector<string> &filenames);
void searchForFile(string filename, path direc, bool recursive, bool case_sen);
void parent_process();


int main(int argc, char* argv[])
{
    bool recursive = false;
    bool case_sen = false;
    string text_direc;
    vector<string> filenames;
    getParameters(recursive, case_sen, text_direc, filenames, argc, argv);
    path direc{text_direc};

    //pid_t pid = fork();
    // splitProcess(pid, filenames);

    //Fork for every filename:
    for(int i = 0; i < filenames.size(); i++){
        pid_t pid = fork();                               // forking child prozess
        if(pid == 0){                                     // forking successful
            string file_to_search = filenames[i];         // file to look for
            searchForFile(file_to_search, direc,
                        recursive, case_sen);             //looking for file in given direc
            _exit(0);
        }
        parent_process();                                 //Zombie-prevention
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

/*
//define child and parent processes.  do we need the function?
void splitProcess(pid_t pid, vector<string> &filenames)
{
    switch(pid){
        case -1: //error
            cout << "Failed to fork" << endl;
            exit(1);
        case 0: //child
            path direc = path.empty() ? current_path() : path{path};
            searchForFile(filename, direc, recursive, case_sen);
            exit(0);
            break;
        default: //parent
            break;
    }

};
*/

void searchForFile(string file_to_search, path direc, bool recursive, bool case_sen){

    //compares 2 names
    auto equals = [&](const string &a, const string &b){
        if(case_sen){ return a == b;}
        string x=a, y=b;
        transform(x.begin(), x.end(), x.begin(), ::tolower);
        transform(y.begin(), y.end(), y.begin(), ::tolower);
        return x == y;
    };

    if(recursive){
        for (const auto &entry : recursive_directory_iterator(direc)) {
            string entry_name = entry.path().filename().string();
            if (equals(entry_name, file_to_search)) {
                cout << getpid() << "File found with child process: "<< file_to_search << ": " << absolute(entry.path()) << endl; //todo: check structure
            }
        }
    }else{
        for(const auto &entry: directory_iterator(direc)){
            string entry_name = entry.path().filename().string();
            if (equals(entry_name, file_to_search)) {
                cout << getpid() << "File found with child process: " << file_to_search << ": " << absolute(entry.path()) << endl; //todo: check structure
            }
        }
    }
}

void parent_process(){
    while (wait(nullptr) > 0){}
}
