//
//  CharacterData.cpp
//  biometrics-02
//
//  Created by Martin Kiesel on 18/03/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include "CharacterData.hpp"

bool CharacterData::readData(const string &fn)
{
    ifstream fin(fn);
    string line;

    while (getline(fin, line))
    {
        char X = line[0];
        int i(0), j(0);
        stringstream stream(line);

        data[X].push_back(vector<int> (16));

        stream.seekg(1);
        while (stream >> i)
        {
            data[X][data[X].size() - 1].at(j) = i;
            if (stream.peek() == ' ')
                stream.ignore();
            j++;
        }

    }
    return 1;
}

int CharacterData::countData(Data &d)
{
    int i(0);
    for (const auto &item : d) i += item.second.size();
    return i;
}

void CharacterData::resetStats()
{
    for (const auto &character : alphabet)
    {
        stats.frequence[character] = 0.0;
        stats.mean.clear();
        stats.variance.clear();
    }
}

void CharacterData::calculateStats()
{
    if (train_size == 0) return;

    CharacterData::resetStats();

    for (const auto &it : train_data)
    {
        char x = it.first;
        size_t it_size = it.second.size();
        vector<int> sum(16, 0);
        vector<double> sumDifference(16, 0);

        for (int i = 0; i < it_size; i++)
            for (int j = 0; j < it.second[i].size(); j++)
                sum[j] += it.second[i][j];

        for (const auto &s : sum)
            stats.mean[x].push_back((double) s / it_size);

        for (int i = 0; i < it_size; i++)
            for (int j = 0; j < it.second[i].size(); j++)
                sumDifference[j] += (it.second[i][j] - stats.mean[x][j]) * (it.second[i][j] - stats.mean[x][j]);

        for (const auto &s : sumDifference)
            stats.variance[x].push_back((double) s / it_size);

        stats.frequence[x] = (double) it_size / train_size;
    }
}

void CharacterData::divide(int _train_size)
{
    mt19937_64 generator(random());
    uniform_int_distribution<> alpha_distribution(0, 25);

    test_data.clear();
    train_data.clear();
    train_size = 0;

    test_data.insert(data.begin(), data.end());

    set<int> not_accesible_characters;

    for (int i = 0; i < _train_size; i++)
    {
        if (not_accesible_characters.size() == test_data.size()) break;

        int alpha_index = alpha_distribution(generator);
        char x = alphabet.at(alpha_index);

        if (!test_data.count(x) || test_data[x].size() == 1)
        {
            i--;
            not_accesible_characters.insert(alpha_index);
            continue;
        }

        uniform_int_distribution<> data_distribution(0, (int) test_data[x].size()-1);
        int data_index = data_distribution(generator);

        train_data[x].push_back(test_data[x][data_index]);
        test_data[x].erase(test_data[x].begin() + data_index);
        train_size++;
    }
    
    test_size = data_size - train_size;
    CharacterData::calculateStats();
}

void CharacterData::makeDeepCopy(const CharacterData &character_data)
{
    copyData(character_data.data, data);
    copyData(character_data.train_data, train_data);
    copyData(character_data.test_data, test_data);

    stats = character_data.stats;
    data_size = countData(data);
    train_size = countData(train_data);
    test_size = data_size - train_size;
};