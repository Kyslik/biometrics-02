//
//  SVMClassifier.cpp
//  biometrics-02
//
//  Created by Martin Kiesel on 21/03/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include "SVMClassifier.hpp"

ReturnStat SVMClassifier::classify()
{
    ReturnStat return_stat;

    Ptr<SVM> svm = SVM::create();

    svm->setType(SVM::C_SVC);
    svm->setC(3);
    svm->setKernel(SVM::POLY);
    svm->setDegree(3);

    svm->train(mat_data.train_data, ROW_SAMPLE, mat_data.train_labels);

    int line = 0;
    for (const auto &it : data.test_data)
    {
        char x = it.first;
        size_t it_size = it.second.size();

        for (int i = 0; i < it_size; i++)
        {
            if ((int) x == svm->predict(mat_data.test_data.row(line))) return_stat.correct_test_count++;
            line++;
        }
    }

    return_stat.test_count = line;
    return_stat.train_size = data.train_size;

    return return_stat;
}

void SVMClassifier::makeMatData()
{
    SVMClassifier::initMat();

    int line = 0;
    for (const auto &it : data.train_data)
    {
        char x = it.first;
        size_t it_size = it.second.size();

        for (int i = 0; i < it_size; i++)
        {
            for (int j = 0; j < it.second[i].size(); j++)
            {
                mat_data.train_data.at<float>(line, j) = (float) it.second[i][j];
            }
            mat_data.train_labels.at<int>(line, 0) = (int) x;
            line++;
        }
    }
    
    line = 0;
    for (const auto &it : data.test_data)
    {
        size_t it_size = it.second.size();

        for (int i = 0; i < it_size; i++)
        {
            for (int j = 0; j < it.second[i].size(); j++)
            {
                mat_data.test_data.at<float>(line, j) = (float) it.second[i][j];
            }
            line++;
        }
    }
}

void SVMClassifier::initMat()
{
    SVMClassifier::clearMatData();

    mat_data.train_data.create(data.train_size, ATTRIBUTE_SIZE, CV_32FC1);
    mat_data.train_labels.create(data.train_size, 1, CV_32SC1);
    mat_data.test_data.create(data.test_size, ATTRIBUTE_SIZE, CV_32FC1);
}

void SVMClassifier::clearMatData()
{
    mat_data.train_data.release();
    mat_data.train_labels.release();
    mat_data.test_data.release();
}