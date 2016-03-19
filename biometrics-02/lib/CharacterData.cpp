//
//  CharacterData.cpp
//  biometrics-02
//
//  Created by Martin Kiesel on 18/03/16.
//  Copyright © 2016 Martin Kiesel. All rights reserved.
//

#include "CharacterData.hpp"

bool CharacterData::readData(Data &d, const string &fn)
{
    ifstream fin(fn);
    string line;

    while (getline(fin, line))
    {
        char X = line[0];
        int i(0), j(0);
        stringstream stream(line);

        d[X].push_back(vector<int> (16));

        stream.seekg(1);
        while (stream >> i)
        {
            d[X][d[X].size() - 1].at(j) = i;
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

void CharacterData::divide(int _train_size)
{
    mt19937_64 generator(random());
    uniform_int_distribution<> alpha_distribution(0, 25);

    test_data.clear();
    train_data.clear();

    test_data.insert(data.begin(), data.end());

    set<int> not_accesible_characters;

    for (int i = 0; i < _train_size; i++)
    {
        if (not_accesible_characters.size() == 26) break;

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
}



