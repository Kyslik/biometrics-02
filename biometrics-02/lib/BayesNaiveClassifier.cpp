//
//  BayesNaiveClassifier.cpp
//  biometrics-02
//
//  Created by Martin Kiesel on 19/03/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include "BayesNaiveClassifier.hpp"

ReturnStat BayesNaiveClassifier::classify()
{
    ReturnStat return_stat;
    map<char, double> classifier;
    using clasifier_type = decltype(classifier)::value_type;

    for (const auto &it : data.test_data)
    {
        char x = it.first;
        size_t it_size = it.second.size();

        for (int i = 0; i < it_size; i++)
        {
            for (const auto &character : alphabet)
                classifier[character] = data.stats.frequence[character];

            for (int j = 0; j < it.second[i].size(); j++)
            {
                for (const auto &character : alphabet)
                {
                    if (classifier[character] == 0) continue;
                        classifier[character] *= data.gaussDistribution(character, j, it.second[i][j]);
                }
            }

            auto pr = max_element (begin(classifier), end(classifier),
                                   [] (const clasifier_type & p1, const clasifier_type & p2) {return p1.second < p2.second;}
                                   );

            if (pr->first == x) return_stat.correct_test_count++;
            return_stat.test_count++;
        }
    }
    return_stat.train_size = data.train_size;
    return return_stat;
}