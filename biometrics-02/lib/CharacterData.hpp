//
//  CharacterData.hpp
//  biometrics-02
//
//  Created by Martin Kiesel on 18/03/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#ifndef CharacterData_hpp
#define CharacterData_hpp

#include <iostream>
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

    CharacterData(const string &file_name)
    {
        if (fileExists(file_name))
            readData(data, file_name);
        data_size = countData(data);
    };

    void divide(int _train_size);

private:
    inline bool fileExists (const string &fn)
    {
        struct stat buff;
        return (stat (fn.c_str(), &buff) == 0);
    }

    bool readData(Data &d, const string &fn);
    int countData(Data &d);
};

#endif /* CharacterData_hpp */
