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
        unsigned long long w[5] = {0};

        if (k.size() <= 6)
        {
            int a[6] = {0};

            for (unsigned int i = 0; i < k.size(); i++)
            {
                a[6 - k.size() + i] = letterDigitToNumber(k[i]);
            }

            unsigned long long val = 0;

            for (int i = 0; i < 6; i++)
            {
                val = val * 36 + a[i];
            }
            
            w[4] = val;
        }
        else 
        {
            int chunk_index = (k.size() + 5) / 6 - 1;

            for (int i = k.size(); i > 0; i -= 6)
            {
                int a[6] = {0};

                int start = max(0, i - 6);  // Start of this chunk
                int len = i - start;             // Chunk length

                for (int j = 0; j < len; ++j)
                {
                    a[6 - len + j] = letterDigitToNumber(k[start + j]);
                }

                unsigned long long val = 0;
                for (int j = 0; j < 6; j++)
                {
                    val = val * 36 + a[j];
                }

                w[chunk_index--] = val;
            }
        }

        return rValues[0]*w[0] + rValues[1]*w[1] + rValues[2]*w[2] + rValues[3]*w[3] + rValues[4]*w[4];
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
       char lowerCase = tolower(letter);
       
       if (lowerCase >= 'a' && lowerCase <= 'z')
       {
            return lowerCase - 'a';
       }

       if (lowerCase >= '0' && lowerCase <= '9')
       {
            return lowerCase - '0' + 26;
       }

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
