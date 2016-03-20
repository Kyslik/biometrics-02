//
//  constants.hpp
//  biometrics-02
//
//  Created by Martin Kiesel on 19/03/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#ifndef constants_h
#define constants_h

#include <vector>
#include <map>
using namespace std;

using Data = map<char, vector<vector<int>>>;

const vector<char> alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

struct ReturnStat
{
    int train_size = 0, test_count = 0, correct_test_count = 0;
};

struct Statistics
{
    map<char, double> frequence;
    map<char, vector<double>> mean, variance;
};

#endif /* constants_h */