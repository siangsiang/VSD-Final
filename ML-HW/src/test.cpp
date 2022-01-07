#include "../include/csvreader.hpp"
#include "../include/FixedPointNumber.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const string filepath = "data/input/1_golden_double_112.dat";

int main()
{
    FILE* fp = fopen(filepath.c_str(), "r");
    char linebuf[1048576];
    unsigned int u;
    while (fscanf(fp, "%[^\n]%*c", linebuf) != EOF) {
        int offset = 0;
        int inc = 0;
        unsigned int u;
        while (sscanf(linebuf+offset, "%x%n", &u, &inc) != EOF) {
            offset += inc;
            FixedPointNumber<3, 12> fp(u);
            cout << fp << ' ';
        }
    }
    return 0;
}