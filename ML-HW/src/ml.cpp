#include "../include/csvreader.hpp"
#include "../include/FixedPointNumber.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdint>

using namespace std;

using FP = FixedPointNumber<3, 28>;

bool read_ecg_input(const string &filepath, vector<FP> &dst)
{
    CSVReader* csv_reader;
    try {
        csv_reader = new CSVReader(filepath);
    } catch (const char* msg) {
        cerr << msg << endl;
        return false;
    }

    vector<uint32_t> csv_data;
    csv_reader->read_hex_line(csv_data);

    dst.clear();
    for (uint32_t u : csv_data) {
        dst.emplace_back(u);
    }
    
    return true;
}

// conv1d_weights[layer_id][filter]
vector<vector<string>> conv1d_weights_filepath;

bool read_conv1d_weights(const string &filepath, vector<vector<FP>> &dst)
{
    CSVReader* csv_reader;
    try {
        csv_reader = new CSVReader(filepath);
    } catch (const char* msg) {
        cerr << msg << endl;
    }

    vector<vector<uint32_t>> csv_data;
    do {
        csv_data.emplace_back();
    }while (csv_reader->read_hex_line(csv_data.back()));

    // the last two lines are empty
    csv_data.pop_back();
    csv_data.pop_back();

    dst.clear();
    for (auto &v : csv_data) {
        dst.emplace_back();
        for (uint32_t u : v) {
            FP fp(u);
            dst.back().emplace_back(u);
        }
    }
    
    return true;
}

void conv1d(int layer_id, vector<vector<FP>> &in, vector<vector<FP>> &out)
{
    const int kernel_size = 5;
    const int stride = 2;
    const int n_filter = conv1d_weights_filepath[layer_id].size();

    vector<vector<vector<FP>>> weights;
    weights.resize(n_filter);
    for (int f = 0; f < n_filter; ++f) {
        read_conv1d_weights(conv1d_weights_filepath[layer_id][f], weights[f]);
    }

    // for (int f = 0; f < n_filter; ++f) {
    //     for (int d = 0; d < weights[f].size(); ++d) {
    //         for (int i = 0; i < weights[f][d].size(); ++i) {
    //             cout << weights[f][d][i] << ' ';
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    out.clear();
    out.resize(n_filter);

    for (int f = 0; f < n_filter; ++f) {
        vector<vector<FP>> &filter = weights[f];
        
        for (int i = filter[0].size()-1; i < in[0].size(); i += stride) {
            FP fp(0u);
            for (int dep = 0; dep < filter.size(); ++dep) {
                vector<FP> &filter_vec = filter[dep];
                vector<FP> &in_vec = in[dep];
                for (int k = 0; k < filter_vec.size(); ++k) {
                    FP product = filter_vec[k] * in_vec[i-k];
                    fp = fp + product;
                }
            }
            out[f].emplace_back(fp);
        }
    }
}

void maxpool1d(const vector<vector<FP>> &in, vector<vector<FP>> &out)
{
    out.clear();
    out.resize(in.size());

    const int stride = 2;

    for (int i = 0; i < in.size(); ++i) {
        for (int j = 0; j < (in[0].size()/2)*2; j += stride) {
            FP maxfp;
            if (in[i][j].get_value() > in[i][j+1].get_value()) {
                maxfp = in[i][j];
            }
            else {
                maxfp = in[i][j+1];
            }
            out[i].emplace_back(maxfp);
        }
    }
}

void flatten(vector<vector<FP>> &in, vector<FP> &out)
{
    out.clear();
    for (auto &v : in) {
        for (FP &fp : v) {
            out.emplace_back(fp);
        }
    }
}

vector<string> fc_weights_filepath;
bool read_fc_weights(const string &filepath, vector<vector<FP>> &dst)
{
    CSVReader* csv_reader;
    try {
        csv_reader = new CSVReader(filepath);
    } catch (const char* msg) {
        cerr << msg << endl;
    }

    vector<vector<uint32_t>> csv_data;
    do {
        csv_data.emplace_back();
    }while (csv_reader->read_hex_line(csv_data.back()));

    // the last two lines are empty
    csv_data.pop_back();
    csv_data.pop_back();

    dst.clear();
    for (auto &v : csv_data) {
        dst.emplace_back();
        for (uint32_t u : v) {
            FP fp(u);
            dst.back().emplace_back(u);
        }
    }
    
    return true;
}

void mat_mul(vector<FP> &x, vector<vector<FP>> &mat, vector<FP> &y)
{
    assert(x.size() == mat[0].size());
    y.clear();
    y.resize(mat.size());
    for (int row = 0; row < mat.size(); ++row) {
        y[row] = 0;
        for (int col = 0; col < mat[0].size(); ++col) {
            FP product = x[col] * mat[row][col];
            y[row] = y[row] + product;
        }
    }
}

void fc(int layer_id, vector<FP> &in, vector<FP> &out)
{
    vector<vector<FP>> weights;
    read_fc_weights(fc_weights_filepath[layer_id], weights);
    mat_mul(in, weights, out);
}

void record_golden(int clz, const string &filepath)
{
    fstream ofs(filepath, ios::out);
    ofs << clz << endl;
}

void record_golden(vector<FP> &v, const string &filepath)
{
    fstream ofs(filepath, ios::out);
    for (auto &fp : v) {
        ofs << fp << "  // " << fp.to_double() << endl;
    }
}

void record_golden(vector<vector<FP>> &m, const string &filepath)
{
    fstream ofs(filepath, ios::out);
    for (auto &v : m) {
        for (auto &fp : v) {
            ofs << fp << "  // " << fp.to_double() << endl;
        }
        ofs << endl;
    }
}

int inference(vector<FP> &in, const string &filename, int ground_truth)
{
    fstream ofs(string("result/logs/")+filename, ios::out);

    vector<vector<FP>> in_2d;
    in_2d.emplace_back(in);
    ofs << "in_2d.shape = (" << in_2d.size() << ", " << in_2d[0].size() << ")" << endl << endl;
    record_golden(in_2d, string("result/input/")+filename);

    ofs << "conv1d_0 start" << endl;
    vector<vector<FP>> conv1d_0_out;
    conv1d(0, in_2d, conv1d_0_out);
    ofs << "conv1d_0_out.shape = (" << conv1d_0_out.size() << ", " << conv1d_0_out[0].size() << ")" << endl;
    record_golden(conv1d_0_out, string("result/conv1d_0_golden/")+filename);
    ofs << "conv1d_0 end" << endl << endl;

    ofs << "maxpool1d_0 start" << endl;
    vector<vector<FP>> maxpool1d_0_out;
    maxpool1d(conv1d_0_out, maxpool1d_0_out);
    ofs << "maxpool1d_0_out.shape = (" << maxpool1d_0_out.size() << ", " << maxpool1d_0_out[0].size() << ")" << endl;
    record_golden(maxpool1d_0_out, string("result/maxpool1d_0_golden/")+filename);
    ofs << "maxpool1d_0 end" << endl << endl;

    ofs << "conv1d_1 start" << endl;
    vector<vector<FP>> conv1d_1_out;
    conv1d(1, maxpool1d_0_out, conv1d_1_out);
    ofs << "conv1d_1_out.shape = (" << conv1d_1_out.size() << ", " << conv1d_1_out[0].size() << ")" << endl;
    record_golden(conv1d_1_out, string("result/conv1d_1_golden/")+filename);
    ofs << "conv1d_1 end" << endl << endl;

    ofs << "maxpool1d_1 start" << endl;
    vector<vector<FP>> maxpool1d_1_out;
    maxpool1d(conv1d_1_out, maxpool1d_1_out);
    ofs << "maxpool1d_1_out.shape = (" << maxpool1d_1_out.size() << ", " << maxpool1d_1_out[0].size() << ")" << endl;
    record_golden(maxpool1d_1_out, string("result/maxpool1d_1_golden/")+filename);
    ofs << "maxpool1d_1 end" << endl << endl;

    ofs << "flatten start" << endl;
    vector<FP> flatten_out;
    flatten(maxpool1d_1_out, flatten_out);
    ofs << "flatten_out.shape = (" << flatten_out.size() << ")" << endl;
    record_golden(flatten_out, string("result/flatten_golden/")+filename);
    ofs << "flatten end" << endl << endl;

    ofs << "fc_0 start" << endl;
    vector<FP> fc_0_out;
    fc(0, flatten_out, fc_0_out);
    ofs << "fc_0_out.shape = (" << fc_0_out.size() << ")" << endl;
    record_golden(fc_0_out, string("result/fc_0_golden/")+filename);
    ofs << "fc_0 end" << endl << endl;
    
    ofs << "fc_1 start" << endl;
    vector<FP> fc_1_out;
    fc(1, fc_0_out, fc_1_out);
    ofs << "fc_1_out.shape = (" << fc_1_out.size() << ")" << endl;
    record_golden(fc_1_out, string("result/fc_1_golden/")+filename);
    ofs << "fc_1 end" << endl << endl;

    double max_v = fc_0_out[0].to_double();
    int max_idx = 0;
    for (int i = 1; i < fc_1_out.size(); ++i) {
        FP &fp = fc_1_out[i];
        if (max_v < fp.to_double()) {
            max_v = fp.to_double();
            max_idx = i;
        }
    }

    ofs << "Groundtruth is: " << ground_truth << endl;
    ofs << "Classified as: " << max_idx << endl;

    if (ground_truth == max_idx) {
        ofs << "Pass" << endl;
    }
    else {
        ofs << "Fail" << endl;
    }

    record_golden(max_idx, string("result/output/")+filename);

    return max_idx;
}

int main(int argc, char* argv[])
{
    conv1d_weights_filepath.emplace_back();
    conv1d_weights_filepath.back().emplace_back("data/weights/Conv1d(1, 5, kernel_size=(5,), stride=(2,))_0.csv");
    conv1d_weights_filepath.back().emplace_back("data/weights/Conv1d(1, 5, kernel_size=(5,), stride=(2,))_1.csv");
    conv1d_weights_filepath.back().emplace_back("data/weights/Conv1d(1, 5, kernel_size=(5,), stride=(2,))_2.csv");
    conv1d_weights_filepath.back().emplace_back("data/weights/Conv1d(1, 5, kernel_size=(5,), stride=(2,))_3.csv");
    conv1d_weights_filepath.back().emplace_back("data/weights/Conv1d(1, 5, kernel_size=(5,), stride=(2,))_4.csv");

    conv1d_weights_filepath.emplace_back();
    conv1d_weights_filepath.back().emplace_back("data/weights/Conv1d(5, 2, kernel_size=(5,), stride=(2,))_0.csv");
    conv1d_weights_filepath.back().emplace_back("data/weights/Conv1d(5, 2, kernel_size=(5,), stride=(2,))_1.csv");

    fc_weights_filepath.emplace_back("data/weights/Linear(in_features=30, out_features=9, bias=False).csv");
    fc_weights_filepath.emplace_back("data/weights/Linear(in_features=9, out_features=5, bias=False).csv");


    if (argc != 2) {
        cerr << "Invalid argument!" << endl;
        exit(1);
    }

    char* filepath = argv[1];
    string filename = string(filepath+string(filepath).find_last_of('/')+1);
    vector<FP> input_fp;

    read_ecg_input(filepath, input_fp);

    int ground_truth = (int)(filename[0] - '0');
    cout << filename << endl;

    int clz = inference(input_fp, filename, ground_truth);
    cout << "Classified as: " << clz << endl;

    return 0;
}