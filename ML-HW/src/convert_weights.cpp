#include "csvreader.hpp"
#include "FixedPointNumber.hpp"
#include "common.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const string srcdir = "rawdata/weights/";
const string dstdir = "data/weights/";

const string files[] = {
    "Conv1d(1, 5, kernel_size=(5,), stride=(2,), bias=False)_0.csv",
    "Conv1d(1, 5, kernel_size=(5,), stride=(2,), bias=False)_1.csv",
    "Conv1d(1, 5, kernel_size=(5,), stride=(2,), bias=False)_2.csv",
    "Conv1d(1, 5, kernel_size=(5,), stride=(2,), bias=False)_3.csv",
    "Conv1d(1, 5, kernel_size=(5,), stride=(2,), bias=False)_4.csv",
    "Conv1d(5, 2, kernel_size=(5,), stride=(2,), bias=False)_0.csv",
    "Conv1d(5, 2, kernel_size=(5,), stride=(2,), bias=False)_1.csv",
    "Linear(in_features=9, out_features=5, bias=False).csv",
    "Linear(in_features=30, out_features=9, bias=False).csv"
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

    // the last two lines should be empty
    data_double.pop_back();
    data_double.pop_back();

    fstream ofs(dstpath, ios::out);

    for (auto &dv : data_double) {
        int i = 0;
        for (double &d : dv) {
            FP fp(d);
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