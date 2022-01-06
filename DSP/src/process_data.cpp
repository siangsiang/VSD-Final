#include "../include/csvreader.hpp"
#include "../include/FixedPointNumber.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    while ((a%=b) && (b%=a))
        ;
    return a+b;
}

int main()
{
    CSVReader* csv_reader;
    try {
        csv_reader = new CSVReader("data/vsdfinal.csv");
    } catch (const char* msg) {
        cerr << msg << endl;
    }

    fstream ofs("data/vsdfinal_processed.csv", ios::out);
    vector<vector<double>> data_double;
    do {
        data_double.emplace_back();
    }while (csv_reader->read_double_line(data_double.back()));
    data_double.pop_back();
    data_double.pop_back();

    vector<int> label;
    for (auto &dv: data_double) {
        label.emplace_back(dv.back() + 0.5);
        dv.pop_back(); // pop the label
    }

    double minv = 1e9;
    for (auto &dv: data_double) {
        for (double &v: dv) {
            v *= 1000;
            minv = min(v, minv);
        }
    }

    for (auto &dv: data_double) {
        for (double &v: dv) {
            v -= minv;
        }
    }

    int gcdv = data_double[0][0] + 0.5;
    for (auto &dv: data_double) {
        for (double &v: dv) {
            if ((int)(v+0.5) != 0)
                gcdv = gcd(gcdv, v+0.5);
        }
    }
    cout << "gcd = " << gcdv << endl;

    for (auto &dv: data_double) {
        for (double &v: dv) {
            v /= gcdv;
        }
    }

    for (int i = 0; i < data_double.size(); ++i) {
        auto &dv = data_double[i];
        for (int j = 0; j < dv.size(); ++j) {
            ofs << (int)(dv[j]+0.5)-512 << ',';
        }
        ofs << label[i];
        ofs << endl;
    }
    ofs.close();

    return 0;
}