#include "../include/csvreader.hpp"
#include "../include/FixedPointNumber.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdint>
#include <dirent.h>

using namespace std;

using FP = FixedPointNumber<3, 12>;

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

bool read_ecg_input(const string &input_filepath, vector<FP> &dst)
{
    CSVReader* csv_reader;
    try {
        csv_reader = new CSVReader(input_filepath);
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

int main(int argc, char* argv[])
{
    string dir = "data/input/";
    vector<string> files;
    listdir(files, dir);
    cout << files.size() << endl;
    sort(files.begin(), files.end());
    vector<vector<string>> cls_files(10);
    for (int c = 0, i = 0; c < 10; ++c) {
        while (i < files.size() && files[i][0]-'0' == c) {
            cls_files[c].emplace_back(files[i]);
            ++i;
        }
    }

    int num[] = {1, 2, 3, 10, 100, 1000, 8497};
    for (int n = 0; n < sizeof(num)/sizeof(int); ++n) {
        int t = 0;
        fstream ofs_b3(string("dram_data/input/input_")+to_string(num[n])+"_b3.hex", ios::out);
        fstream ofs_b2(string("dram_data/input/input_")+to_string(num[n])+"_b2.hex", ios::out);
        fstream ofs_b1(string("dram_data/input/input_")+to_string(num[n])+"_b1.hex", ios::out);
        fstream ofs_b0(string("dram_data/input/input_")+to_string(num[n])+"_b0.hex", ios::out);
        fstream ofs_golden(string("dram_data/golden/golden_")+to_string(num[n])+".hex", ios::out);
        fstream ofs_ground(string("dram_data/ground_truth/ground_truth_")+to_string(num[n])+".hex", ios::out);
        vector<int> cls_idx(10, 0);
        bool done = false;
        while (!done) {
            for (int c = 0; c < 10; ++c) {
                if (cls_idx[c] < cls_files[c].size()) {
                    string result_dir      = "result/output/";
                    string result_filename = cls_files[c][cls_idx[c]];
                    string result_filepath = result_dir + result_filename;
                    fstream ifs(result_filepath, ios::in);
                    int result;
                    ifs >> result;

                    string input_filename  = cls_files[c][cls_idx[c]];
                    string input_filepath  = dir + input_filename;
                    cout << input_filepath << endl;

                    cls_idx[c]++;

                    vector<FP> input_fp;
                    read_ecg_input(input_filepath, input_fp);

                    ofs_golden << uppercase << hex << setfill('0') << setw(2) << "00";
                    ofs_golden << uppercase << hex << setfill('0') << setw(2) << result;
                    ofs_golden << uppercase << hex << setfill('0') << setw(2) << "00";
                    ofs_golden << uppercase << hex << setfill('0') << setw(2) << "00";
                    ofs_golden << '\n';

                    ofs_ground << uppercase << hex << setfill('0') << setw(2) << "00";
                    ofs_ground << uppercase << hex << setfill('0') << setw(2) << c;
                    ofs_ground << uppercase << hex << setfill('0') << setw(2) << "00";
                    ofs_ground << uppercase << hex << setfill('0') << setw(2) << "00";
                    ofs_ground << '\n';

                    for (FP &fp : input_fp) {
                        ofs_b3 << uppercase << hex << setfill('0') << setw(2) << ((fp.get_value() >> 8) & 0xFF) << '\n';
                        ofs_b2 << uppercase << hex << setfill('0') << setw(2) << ((fp.get_value() >> 0) & 0xFF) << '\n';
                        ofs_b1 << uppercase << hex << setfill('0') << setw(2) << "00" << '\n';
                        ofs_b0 << uppercase << hex << setfill('0') << setw(2) << "00" << '\n';
                    }

                    t++;
                    if (t == num[n] || t == files.size()) {
                        done = true;
                        break;
                    }
                }
            }
        }
    }

    return 0;
}