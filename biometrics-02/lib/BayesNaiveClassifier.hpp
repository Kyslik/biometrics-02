//
//  BayesNaiveClassifier.hpp
//  biometrics-02
//
//  Created by Martin Kiesel on 19/03/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#ifndef BayesNaiveClassifier_hpp
#define BayesNaiveClassifier_hpp

#include <math.h>

#include "CharacterData.hpp"
#include "constants.hpp"

using namespace std;

class BayesNaiveClassifier
{
public:
    CharacterData data;

    BayesNaiveClassifier() {};
    BayesNaiveClassifier(CharacterData _data)
    {
        data = _data;
    };
    BayesNaiveClassifier(CharacterData _data, int train_size)
    {
        data = _data;
        data.divide(train_size);
    };

    inline void setData(CharacterData _data)
    {
        data = _data;
    }

    inline void divide(int train_size)
    {
        data.divide(train_size);
    }

    ReturnStat classify();
private:
    
};



#endif /* BayesNaiveClassifier_hpp */