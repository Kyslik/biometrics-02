//
//  CharacterData.hpp
//  biometrics-02
//
//  Created by Martin Kiesel on 18/03/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#ifndef CharacterData_hpp
#define CharacterData_hpp


#include <fstream>
#include <sstream>
#include <random>
#include <set>
#include <sys/stat.h>
#include <unistd.h>

#include "constants.hpp"

using namespace std;

class CharacterData
{
    int data_size = 0;
    Data data;
    random_device random;

public:
    int train_size = 0, test_size = 0;
    Data train_data, test_data;
    Statistics stats;

    CharacterData() {}
    CharacterData(const string &file_name)
    {
        if (fileExists(file_name))
            readData(file_name);
        data_size = countData(data);
    };
    CharacterData(const CharacterData &character_data)
    {
        makeDeepCopy(character_data);
    }
    CharacterData& operator=(const CharacterData &character_data)
    {
        if (this != &character_data)
            makeDeepCopy(character_data);
        return *this;
    }

    inline double gaussDistribution(const char character, int position, int x)
    {
        double variance = stats.variance[character][position];
        double mean = stats.mean[character][position];
        return exp(((x - mean) * (x - mean)) / (-2 * variance)) / sqrt(2 * M_PI * variance);
    }

    void divide(int _train_size);

private:
    inline bool fileExists (const string &fn)
    {
        struct stat buff;
        return (stat (fn.c_str(), &buff) == 0);
    }

    inline void copyData(const Data &from, Data &to)
    {
        to.clear();
        to.insert(from.begin(), from.end());
    }

    void makeDeepCopy(const CharacterData &character_data);
    void resetStats();
    void calculateStats();
    bool readData(const string &fn);
    int countData(Data &d);
};

#endif /* CharacterData_hpp */