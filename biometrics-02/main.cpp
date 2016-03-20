//
//  main.cpp
//  biometrics-02
//
//  Created by Martin Kiesel on 15/03/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include <iostream>
#include <utility>

#include "constants.hpp"
#include "CharacterData.hpp"
#include "BayesNaiveClassifier.hpp"

using namespace std;

const char* DATA_FILE = "./data.txt";

int main(int argc, const char * argv[])
{
    CharacterData data(DATA_FILE);

    vector<vector<ReturnStat>> stats(10);
    vector<ReturnStat> final_stats;

    BayesNaiveClassifier bayes_classifier(data);

    for (int i = 0; i < stats.size(); i++)
    {
        for (int j = 50; j <= 900; j += 50)
        {
            bayes_classifier.data.divide(j);
            stats[i].push_back(bayes_classifier.classify());
        }
    }

    final_stats.resize(stats[0].size());

    for (int i = 0; i < stats.size(); i++) {
        for (int j = 0; j < stats[i].size(); j++) {
            final_stats[j].test_count += stats[i][j].test_count;
            final_stats[j].train_size += stats[i][j].train_size;
            final_stats[j].correct_test_count += stats[i][j].correct_test_count;
        }
    }

    for (auto &st : final_stats)
    {
        st.test_count /= stats.size();
        st.train_size /= stats.size();
        st.correct_test_count /= stats.size();
        float p = (float) st.correct_test_count / (float) st.test_count;
        cout << st.train_size << "," << st.test_count << "," << st.correct_test_count << "," << p * 100 << endl;
    }

    return 0;
}