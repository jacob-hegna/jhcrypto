/**
 * analysis.cpp
 * @author: jacob hegna <jacobhegna@gmail.com>
 * @date: April 2017
 * @comment: simple string analysis
 */

#include "analysis.h"

float jhc::digraph_test(std::string str) {
    // common digraphs, includes space
    static const std::string expected[] = {
        "th",
        "he",
        "in",
        "er",
        "an",
        "re",
        "nd",
        "at",
        "on",
        "nt",
        "ha",
        "es",
        "st",
        "en",
        "ed",
        "to",
        "it",
        "ou",
        "ea",
        "hi",
        "is",
        "or",
        "ti",
        "as",
        "te",
        "et",
        " "
    };

    // turn it all lowercase
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    // count digraph occurrences
    float total = 0;
    for(uint i = 0; i < 27; ++i) {
        std::string::size_type pos = 0;
        while((pos = str.find(expected[i], pos)) != std::string::npos) {
            ++total;
            pos += expected[i].size();
        }
    }

    // return 1.0/total if total isn't 0, return 100.0 if it is
    // this ensures our descending sorts work as expected in xor cracking
    return (total > 0) ? 1.0 / total : 100.0;
}

float jhc::letter_test(std::string str) {

    // distribution from https://en.wikipedia.org/wiki/Letter_frequency
    static const float expected[] = {
        0.08167,  // a
        0.01492,  // b
        0.02782,  // c
        0.04253,  // d
        0.12702,  // e
        0.02228,  // f
        0.02015,  // g
        0.06094,  // h
        0.06996,  // i
        0.00153,  // j
        0.00772,  // k
        0.04025,  // l
        0.02406,  // m
        0.06749,  // n
        0.07507,  // o
        0.01929,  // p
        0.00095,  // q
        0.05987,  // r
        0.06327,  // s
        0.09056,  // t
        0.02758,  // u
        0.00978,  // p
        0.02360,  // v
        0.00150,  // w
        0.01974,  // y
        0.00074   // z
    };

    // turn it all lowercase
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    // count our observed character counts
    float observed[26] = {0};
    for(char i = 'a'; i < 'z'; ++i) {
        for(char& c : str) {
            if(i == c) ++observed[i - 'a'];
        }
    }

    // normalize
    for(auto& o : observed) {
        o /= (float)str.size();
    }

    // perform the Pearson chi-squared test
    float statistic = 0;
    for(uint i = 0; i < 26; ++i) {
        statistic += pow(observed[i] - expected[i], 2) / expected[i];
    }
    statistic *= str.size();

    return statistic;
}

uint jhc::hdistance(std::string a, std::string b) {
    uint hdistance = 0;

    // strings need to be of the same size
    if(a.size() != b.size()) return -1;

    // iterate through each byte in the strings
    for(uint i = 0; i < a.size(); ++i) {
        char byte_a = a[i],
             byte_b = b[i];

        // iterate through each bit in the bytes
        for(uint j = 0; j < 8; ++j) {
            if((byte_a & 0b1) != (byte_b & 0b1)) ++hdistance;
            byte_a >>= 1;
            byte_b >>= 1;
        }
    }

    return hdistance;
 }