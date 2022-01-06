#include "../include/csvreader.hpp"
#include "../include/FixedPointNumber.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const string srcdir = "rawdata/input/";
const string dstdir = "data/input/";

const string files[] = {
    "1_golden_double_112.dat"
};

void convert_fp(string srcpath, string dstpath)
{
    cout << srcpath << endl;
    cout << dstpath << endl;
    CSVReader* csv_reader;
    try {
        csv_reader = new CSVReader(srcpath);
    } catch (const char* msg) {
        cerr << msg << endl;
    }

    vector<vector<double>> data_double;
    do {
        data_double.emplace_back();
    }while (csv_reader->read_double_line(data_double.back()));

    data_double.pop_back();

    fstream ofs(dstpath, ios::out);

    for (auto &dv : data_double) {
        int i = 0;
        for (double &d : dv) {
            FixedPointNumber<3, 28> fp(d);
            ofs << fp;
            ++i;
            if (i != dv.size()) {
                ofs << ',';
            }
        }
        ofs << endl;
    }

    ofs.close();
}

int main()
{
    const int n_files = sizeof(files) / sizeof(string);
    for (int i = 0; i < n_files; ++i) {
        string srcpath = srcdir + files[i];
        string dstpath = dstdir + files[i];
        convert_fp(srcpath, dstpath);
    }
    return 0;
}