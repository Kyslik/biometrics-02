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

const char* DATA_FILE = "./data-short.txt";

bool fileExists (const string &fn);
bool readData(map<char, vector<vector<int>>> &d);

int main(int argc, const char * argv[])
{
    map<char, vector<vector<int>>> data;
    if (!readData(data)) return 1;
    //data has all the values from file
    return 0;
}


inline bool fileExists (const string& fn)
{
    struct stat buff;
    return (stat (fn.c_str(), &buff) == 0);
}

bool readData(map<char, vector<vector<int>>> &d)
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
