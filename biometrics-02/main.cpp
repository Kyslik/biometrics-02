//
//  main.cpp
//  biometrics-02
//
//  Created by Martin Kiesel on 15/03/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include <iostream>

#include "constants.hpp"
#include "CharacterData.hpp"
#include "BayesNaiveClassifier.hpp"
#include "SVMClassifier.hpp"

using namespace std;

const char* DATA_FILE = "./data.txt";
const int CROSS_VALIDATION = 10;

int main(int argc, const char * argv[])
{
    CharacterData data(DATA_FILE);

    vector<vector<ReturnStat>> b_stats(CROSS_VALIDATION), s_stats(CROSS_VALIDATION);
    vector<ReturnStat> final_b_stats, final_s_stats;

    BayesNaiveClassifier bayes_classifier;
    SVMClassifier svm_classifier;

    for (int i = 0; i < CROSS_VALIDATION; i++)
    {
        for (int j = 50; j <= 1400; j += 50)
        {
            data.divide(j);
            bayes_classifier.setData(data);
            svm_classifier.setData(data);

            b_stats[i].push_back(bayes_classifier.classify());
            s_stats[i].push_back(svm_classifier.classify());

            if (j >= 400) j += 50;
        }
    }

    final_b_stats.resize(b_stats[0].size());
    final_s_stats.resize(s_stats[0].size());

    for (int i = 0; i < CROSS_VALIDATION; i++) {
        for (int j = 0; j < b_stats[i].size(); j++) {
            final_b_stats[j].test_count += b_stats[i][j].test_count;
            final_b_stats[j].train_size += b_stats[i][j].train_size;
            final_b_stats[j].correct_test_count += b_stats[i][j].correct_test_count;

            final_s_stats[j].test_count += s_stats[i][j].test_count;
            final_s_stats[j].train_size += s_stats[i][j].train_size;
            final_s_stats[j].correct_test_count += s_stats[i][j].correct_test_count;
        }
    }

    for (auto &st : final_b_stats)
    {
        st.test_count /= CROSS_VALIDATION;
        st.train_size /= CROSS_VALIDATION;
        st.correct_test_count /= CROSS_VALIDATION;
        float p = (float) st.correct_test_count / (float) st.test_count;
        cout << st.train_size << "," << st.test_count << "," << st.correct_test_count << "," << p * 100 << endl;
    }
    cout << endl << endl;
    for (auto &st : final_s_stats)
    {
        st.test_count /= CROSS_VALIDATION;
        st.train_size /= CROSS_VALIDATION;
        st.correct_test_count /= CROSS_VALIDATION;
        float p = (float) st.correct_test_count / (float) st.test_count;
        cout << st.train_size << "," << st.test_count << "," << st.correct_test_count << "," << p * 100 << endl;
    }

    return 0;
}