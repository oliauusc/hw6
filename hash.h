#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        const int MAX_STRINGS = 5;
        const int STRING_SIZE = 6;
        unsigned long long w[MAX_STRINGS] = {0};

        int len = k.length();
        int groupIndex = MAX_STRINGS - 1;

        for(int i = len; i > 0 && groupIndex >= 0; i -= STRING_SIZE, --groupIndex) {
            unsigned long long value = 0;
            unsigned long long multiplier = 1;

            for(int j = i - 1; j >= std::max(0, i - STRING_SIZE); --j) {
                char c = std::tolower(k[j]);
                int mapped = static_cast<int>(letterDigitToNumber(c));
                value += mapped * multiplier;
                multiplier *= 36;
            }
            w[groupIndex] = value;
        }

        unsigned long long hash = 0;
        for(int i = 0; i < MAX_STRINGS; ++i) {
            hash += rValues[i] * w[i];
        }

        return static_cast<HASH_INDEX_T>(hash);

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (std::isalpha(letter))
          return std::tolower(letter) -'a';
        if (std::isdigit(letter))
          return 26 + (letter -'0');
          
          return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
