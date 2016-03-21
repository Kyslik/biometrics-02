//
//  SVMClassifier.hpp
//  biometrics-02
//
//  Created by Martin Kiesel on 21/03/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#ifndef SVMClassifier_hpp
#define SVMClassifier_hpp

#include "opencv2/core.hpp"
#include "opencv2/ml.hpp"
#include "CharacterData.hpp"

using namespace std;
using namespace cv;
using namespace cv::ml;

struct MatData
{
    Mat train_data;
    Mat train_labels;
    Mat test_data;
};

class SVMClassifier
{
public:
    CharacterData data;

    SVMClassifier() {};
    SVMClassifier(CharacterData _data)
    {
        data = _data;
        makeMatData();
    };
    SVMClassifier(CharacterData _data, int train_size)
    {
        data = _data;
        data.divide(train_size);
        makeMatData();
    };

    void setData(CharacterData _data)
    {
        data = _data;
        makeMatData();
    }

    ReturnStat classify();
    
private:
    MatData mat_data;
    void makeMatData();
    void clearMatData();
    void initMat();
};

#endif /* SVMClassifier_hpp */
