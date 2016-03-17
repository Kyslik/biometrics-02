//
//  main.cpp
//  biometrics-02
//
//  Created by Martin Kiesel on 15/03/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <utility>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;
using Data = map<char, vector<vector<int>>>;
using DataSize = map<string, int>;

const char* DATA_FILE = "./data-short.txt";

bool fileExists (const string &fn);
bool readData(Data &d);

int divideData(int trainSize, Data &trainData, Data &testData);
int countData(Data &d);

bool setDataSize(DataSize &s, Data &d, int trainSize);

int main(int argc, const char * argv[])
{
    Data data, testData, trainData;
    DataSize dataSize;

    if (!readData(data)) return 1;
    if (!setDataSize(dataSize, data, 5)) return 1;

    return 0;
}


inline bool fileExists (const string& fn)
{
    struct stat buff;
    return (stat (fn.c_str(), &buff) == 0);
}

int divideData(const DataSize dataSize, Data &trainData, Data &testData)
{
    return 0;
}

int countData(Data &d)
{
    int i(0);
    for (const auto &item : d) i += item.second.size();
    return i;
}

bool setDataSize(DataSize &s, Data &d, const int trainSize)
{
    if (s.find("dataSize") == s.end()) s["dataSize"] = countData(d);
    if (trainSize >= s["dataSize"]) return 0;
    s["trainSize"] = trainSize;
    s["testSize"] = s["dataSize"] - trainSize;
    return 1;
}

bool readData(Data &d)
{
    if (!fileExists(DATA_FILE)) return 0;

    ifstream fin(DATA_FILE);
    string line;

    while (getline(fin, line))
    {
        char X = line[0];
        int i(0), j(0);
        stringstream stream(line);

        d[X].push_back(vector<int> (16));

        stream.seekg(1);
        while (stream >> i)
        {

            d[X][d[X].size() - 1].at(j) = i;
            if (stream.peek() == ' ')
                stream.ignore();
            j++;
        }
        
    }
    return 1;
}
