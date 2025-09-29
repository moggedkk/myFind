#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <cctype> //for toupper/tolower


using namespace std;
using namespace std::filesystem;

void getParameters(bool &recursive, bool &case_sen, string &path, vector<string> &filenames, int, char*[]);
void splitProcess(pid_t pid, vector<string> &filenames);
void searchForFile(string, path);


int main(int argc, char* argv[])
{
    bool recursive = false;
    bool case_sen = false;
    string path;
    vector<string> filenames;
    getParameters(recursive, case_sen, path, filenames, argc, argv);

    //pid_t pid = fork();
    // splitProcess(pid, filenames);

    //Fork for every filename:
    for(int i = 0; i < filenames.size(); i++){
        pid_t pid = fork();                               // forking child prozess
        if(pid == 0){                                     // forking successful
            string file_to_search = filenames[i];         // file to look for
            searchForFile(file_to_search,current_path()); //looking for file in given direc
            _exit(0);
        }
    }

    return 0;
}


void getParameters(bool &recursive, bool &case_sen, string &path, vector<string> &filenames, int argc, char* argv[]){

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
        if(optind < argc ){
            path = argv[optind];
            for (int i = optind+1; i < argc; i++) {
                filenames.push_back(argv[i]);
            }
        }

}

//define child and parent processes
void splitProcess(pid_t pid, vector<string> &filenames)
{
    switch(pid){
        case -1: //error
            cout << "Failed to fork" << endl;
            exit(1);
        case 0: //child
        //searchFile();
            break;

        default: //parent
            sleep(1); //todo: wait for child process
            path dpath = current_path();
            cout << dpath << endl;
            for(const auto &entry:
                    directory_iterator(dpath)){
                    cout << "File: " << entry.path().filename() << endl;
            }
    }

};

void searchForFile(string filename, path direc){
    for(const auto &entry: directory_iterator(direc)){
        if(entry.path().filename()  == filename){
            cout << "File found with child prozess: " << entry.path().filename() << endl;
        }
    }
}

