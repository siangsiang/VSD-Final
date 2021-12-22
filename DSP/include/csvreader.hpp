#ifndef __CSVREADER__
#define __CSVREADER__

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class CSVReader
{
public:
    inline CSVReader(std::string filepath)
    {
        fs.open(filepath, std::ios::in);
        if (fs.fail()) {
            throw "Cannot open file";
        }
        line_stream.getline(nullptr, 0);
    }

    inline bool read_double(double &dst)
    {
        if (line_stream.eof())
        {
            if (read_line_buf() == false)
                return false;
        }
        char buf[32];
        line_stream.getline(buf, 32, ',');
        dst = std::atof(buf);
        return true;
    }

    inline bool read_double_line(std::vector<double> &dst)
    {
        if (line_stream.eof())
        {
            if (read_line_buf() == false)
                return false;
        }
        dst.clear();
        char buf[32];
        while (!line_stream.eof()) {
            line_stream.getline(buf, 32, ',');
            dst.emplace_back(std::atof(buf));
        }
        return true;
    }

    inline bool read_int(int &dst)
    {
        if (line_stream.eof())
        {
            if (read_line_buf() == false)
                return false;
        }
        char buf[32];
        line_stream.getline(buf, 32, ',');
        dst = std::atoi(buf);
        return true;
    }

    inline bool read_int_line(std::vector<int> &dst)
    {
        if (line_stream.eof())
        {
            if (read_line_buf() == false)
                return false;
        }
        dst.clear();
        char buf[32];
        while (!line_stream.eof()) {
            line_stream.getline(buf, 32, ',');
            dst.emplace_back(std::atoi(buf));
        }
        return true;
    }

private:
    std::fstream fs;
    std::string line_buf;
    std::stringstream line_stream;

    inline bool read_line_buf()
    {
        if (fs.eof())
            return false;
        std::getline(fs, line_buf, '\n');
        line_stream.clear();
        line_stream.str(line_buf);
        return true;
    }
};

#endif