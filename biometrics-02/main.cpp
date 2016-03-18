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
#include <random>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;
using Data = map<char, vector<vector<int>>>;
using DataSize = map<string, int>;

const char* DATA_FILE = "./data-short.txt";
const vector<char> alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};


bool fileExists (const string &fn);
bool readData(Data &d);

int divideData(int trainSize, Data &trainData, Data &testData, Data &allData);
int countData(Data &d);

bool setDataSize(DataSize &s, Data &d, int trainSize);

int main(int argc, const char * argv[])
{
    //vector<Data> data(3);
    Data allData, testData, trainData;
    DataSize dataSize;

    random_device random;
    mt19937_64 generator(random());

    uniform_int_distribution<> distribution(0, 26);

    distribution(generator);

    if (!readData(allData)) return 1;
    if (!setDataSize(dataSize, allData, 10)) return 1;

    return 0;
}


int divideData(const DataSize dataSize, Data &trainData, Data &testData, Data &allData)
{

    for (int i = 0; i < dataSize.at("all"); i++) {

    }
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
    if (s.find("all") == s.end()) s["all"] = countData(d);
    if (trainSize >= s["all"]) return 0;
    s["train"] = trainSize;
    s["test"] = s["all"] - trainSize;
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

inline bool fileExists (const string& fn)
{
    struct stat buff;
    return (stat (fn.c_str(), &buff) == 0);
}