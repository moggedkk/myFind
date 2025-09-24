#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <vector>

using namespace std;
using namespace std::filesystem;
void getParameters(bool &recursive, bool &case_sen, string &path, vector<string> &filenames, int, char*[]);
int main(int argc, char* argv[])
{
    bool recursive = false;
    bool case_sen = false;
    string path;
    vector<string> filenames;
    // List files in default direc
    getParameters(recursive, case_sen, path, filenames, argc, argv);



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

