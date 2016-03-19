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

using namespace std;

const char* DATA_FILE = "./data-short.txt";

int main(int argc, const char * argv[])
{

    CharacterData data(DATA_FILE);
    data.divide(20);
    
    return 0;
}