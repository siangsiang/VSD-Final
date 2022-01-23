#include "csvreader.hpp"
#include "FixedPointNumber.hpp"
#include "common.hpp"

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

template <typename T1>
vector<T1> convolution(vector<T1> x, vector<T1> h) {
    vector<T1> y;
    for (int i = h.size() - 1; i < x.size(); ++i) {
        T1 yi = 0;
        for (int k = 0; k < h.size(); ++k) {
            if (0 <= i-k && i-k < x.size()) {
                yi = yi + x[i-k] * h[k];
            }
        }
        y.emplace_back(yi);
    }
    return y;
}

int main()
{
    CSVReader* csv_reader;
    try {
        csv_reader = new CSVReader("data/filter_coeff.csv");
    } catch (const char* msg) {
        cerr << msg << endl;
    }

    vector<double> fir_coeff_double;
    vector<FP> fir_coeff_fixed;
    csv_reader->read_double_line(fir_coeff_double);
    for (double d : fir_coeff_double) {
        cout << d << ' ';
    }
    cout << endl;
    for (double d : fir_coeff_double) {
        fir_coeff_fixed.emplace_back(d);
    }
    delete csv_reader;

    {
        fstream ofs("result/fir_coeff.sv", ios::out);
        int i = 0;
        ofs << "wire [15:0] FIR_C [99:0];" << endl;
        for (auto &fp : fir_coeff_fixed) {
            ofs << "assign FIR_C[" << i << "] = 16'h" << fp << ";";
            ofs << "    // " << fixed << setprecision(20) << fp.to_double() << endl;
            i++;
        }
    }


    try {
        csv_reader = new CSVReader("data/vsdfinal_processed.csv");
    } catch (const char* msg) {
        cerr << msg << endl;
    }

    vector<vector<int>> data_2d_int;
    vector<vector<double>> data_2d_double;
    vector<vector<FP>> data_2d_fixed;
    do {
        data_2d_int.emplace_back();
    }while (csv_reader->read_int_line(data_2d_int.back()));
    delete csv_reader;
    data_2d_int.pop_back();

    vector<int> data_label;
    for (int i = 0; i < data_2d_int.size(); ++i) {
        data_label.emplace_back(data_2d_int[i].back());
        data_2d_int[i].pop_back();
        // cout << data_label[i] << ' ';
    }

    for (auto &dv : data_2d_int) {
        data_2d_double.emplace_back();
        data_2d_fixed.emplace_back();
        if (FRAC_BITS >= 10) {
            for (auto &v : dv) {
                data_2d_double.back().emplace_back((double)v / 1024.0);
                data_2d_fixed.back().emplace_back(v << (FRAC_BITS-10));
            }
        }
        else {
            for (auto &v : dv) {
                data_2d_double.back().emplace_back((double)v / 1024.0);
                data_2d_fixed.back().emplace_back(v >> (10-FRAC_BITS));
            }
        }
    }

    for (int t = 0; t < data_2d_int.size() - 1; ++t)
    {
        {
            int i = 0;
            fstream ofs(string("result/input/") + to_string(data_label[t]) + "_input_" + to_string(t) + ".dat", ios::out);
            for (auto &fp : data_2d_fixed[t]) {
                if (fp.is_overflowed() || fp.is_underflowed()) {
                    if (fp.is_overflowed()) {
                        cerr << "WARNING: overflowed after conversion:";
                        cerr << data_2d_double[t][i] << ' ' << data_2d_fixed[t][i].to_double() << endl;
                    }
                    if (fp.is_underflowed()) {
                        cerr << "WARNING: underflowed after conversion:";
                        cerr << data_2d_double[t][i] << ' ' << data_2d_fixed[t][i].to_double() << endl;
                    }
                    throw "ERROR";
                }
                ofs << fp;
                ofs << "    // " << i << ": " << fixed << setprecision(20) << fp.to_double() << endl;
                i++;
            }
        }

        {
            int i = 0;
            fstream ofs(string("result/input_double/") + to_string(data_label[t]) + "_input_double_" + to_string(t) + ".dat", ios::out);
            for (auto &dbl : data_2d_double[t]) {
                ofs << fixed << setprecision(20) << dbl;
                i++;
                if (i != data_2d_double[t].size())
                    ofs << ',';
            }
            ofs << endl;
        }

        vector<FP> y = convolution(data_2d_fixed[t], fir_coeff_fixed);

        {
            int i = 0;
            fstream ofs(string("result/golden/") + to_string(data_label[t]) + "_golden_" + to_string(t) + ".dat", ios::out);
            for (auto &fp : y) {
                if (fp.is_overflowed() || fp.is_underflowed()) {
                    if (fp.is_overflowed()) {
                        cerr << "WARNING: overflowed after convolution: [" << t << "][" << i << "]" << endl;
                        cerr << fp << ' ' << fp.to_double() << endl;
                    }
                    if (fp.is_underflowed()) {
                        cerr << "WARNING: underflowed after convolution: [" << t << "][" << i << "]" << endl;
                        cerr << fp << ' ' << fp.to_double() << endl;
                    }
                    throw "ERROR";
                }
                ofs << fp;
                ofs << "    // " << i << ": " << fixed << setprecision(20) << fp.to_double() << endl;
                i++;
            }
        }

        {
            int i = 0;
            fstream ofs(string("result/golden_double/") + to_string(data_label[t]) + "_golden_double_" + to_string(t) + ".dat", ios::out);
            for (auto &fp : y) {
                if (fp.is_overflowed() || fp.is_underflowed()) {
                    if (fp.is_overflowed()) {
                        cerr << "WARNING: overflowed after convolution: [" << t << "][" << i << "]" << endl;
                        cerr << fp << ' ' << fp.to_double() << endl;
                    }
                    if (fp.is_underflowed()) {
                        cerr << "WARNING: underflowed after convolution: [" << t << "][" << i << "]" << endl;
                        cerr << fp << ' ' << fp.to_double() << endl;
                    }
                    throw "ERROR";
                }
                ofs << fixed << setprecision(20) << fp.to_double();
                i++;
                if (i != y.size())
                    ofs << ',';
            }
        }

        vector<FP> y_norm;

        {
            int i = 0;
            int max_idx = 0;
            double max_d = y[0].to_double();
            int min_idx = 0;
            double min_d = y[0].to_double();

            for (int i = 0; i < y.size(); ++i) {
                auto &fp = y[i];
                if (fp.to_double() > max_d) {
                    max_idx = i;
                    max_d = fp.to_double();
                }
                if (fp.to_double() < min_d) {
                    min_idx = i;
                    min_d = fp.to_double();
                }
            }

            FP min_fixed = y[min_idx];
            FP max_fixed = y[max_idx];
            FP denominator = max_fixed - min_fixed;
            for (int i = 0; i < y.size(); ++i) {
                auto fp = y[i];
                fp = fp - min_fixed;
                fp = fp / denominator;
                if (fp.is_overflowed() || fp.is_underflowed()) {
                    if (fp.is_overflowed()) {
                        cerr << "WARNING: overflowed after normalizing: [" << t << "][" << i << "]" << endl;
                        cerr << fp << ' ' << fp.to_double() << endl;
                    }
                    if (fp.is_underflowed()) {
                        cerr << "WARNING: underflowed after normalizing: [" << t << "][" << i << "]" << endl;
                        cerr << fp << ' ' << fp.to_double() << endl;
                    }
                    // throw "ERROR";
                }
                y_norm.emplace_back(fp);
            }

            {
                i = 0;
                fstream ofs(string("result/golden_norm/") + to_string(data_label[t]) + "_golden_norm_" + to_string(t) + ".dat", ios::out);
                for (auto &fp : y_norm) {
                    ofs << fp;
                    ofs << "    // " << i << ": " << fixed << setprecision(20) << fp.to_double() << endl;
                    i++;
                }
            }
            {
                i = 0;
                fstream ofs(string("result/golden_norm_double/") + to_string(data_label[t]) + "_golden_norm_double_" + to_string(t) + ".dat", ios::out);
                for (auto &fp : y_norm) {
                    ofs << fixed << setprecision(20) << fp.to_double();
                    i++;
                    if (i != y_norm.size())
                        ofs << ',';
                }
            }
        }
    }
    return 0;
}