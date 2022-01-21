#include "csvreader.hpp"
#include "FixedPointNumber.hpp"
#include "common.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <dirent.h>
#include <cstdint>

using namespace std;

const string srcdir = "rawdata/input/";
const string dstdir = "data/input/";

int listdir(vector<string> &filelist, string dirpath)
{
    filelist.clear();
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (dirpath.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            // printf ("%s\n", ent->d_name);
            if (ent->d_name[0] != '.')
                filelist.emplace_back(ent->d_name);
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
}

void convert_fp(string srcpath, string dstpath)
{
    cout << srcpath << endl;
    cout << dstpath << endl;
    
    vector<uint32_t> v;
    FILE* fp = fopen(srcpath.c_str(), "r");
    char linebuf[1024];
    while (fscanf(fp, "%[^\n]%*c", linebuf) != EOF) {
        uint32_t u;
        sscanf(linebuf, "%x", &u);
        v.emplace_back(u);
    }

    fstream ofs(dstpath, ios::out);

    int i = 0;
    for (uint32_t &u : v) {
        FP fp(u);
        ofs << fp;
        ++i;
        if (i != v.size()) {
            ofs << ',';
        }
    }
    ofs << endl;

    ofs.close();
}

int main()
{
    vector<string> files;
    listdir(files, "rawdata/input");
    for (int i = 0; i < files.size(); ++i) {
        string srcpath = srcdir + files[i];
        string dstpath = dstdir + files[i];
        convert_fp(srcpath, dstpath);
    }
    return 0;
}