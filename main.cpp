#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <vector>
#include <sys/types.h>


using namespace std;
using namespace std::filesystem;

void getParameters(bool &recursive, bool &case_sen, string &path, vector<string> &filenames, int, char*[]);
void splitProcess(pid_t pid, vector<string> &filenames);


int main(int argc, char* argv[])
{
    bool recursive = false;
    bool case_sen = false;
    string path;
    vector<string> filenames;
    pid_t pid = fork();
    // List files in default direc
    getParameters(recursive, case_sen, path, filenames, argc, argv);
    splitProcess(pid, filenames);

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
                    cout << "File: " << entry.path() << endl;
            break;
            }
    }

};

