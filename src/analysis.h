/**
 * analysis.h
 * @author: jacob hegna <jacobhegna@gmail.com>
 * @date: April 2017
 * @comment: simple string analysis
 */

#ifndef __ANALYSIS_H_
#define __ANALYSIS_H_

#include <cmath>
#include <algorithm>

namespace jhc {

    /**
     * digraph_test(std::string)
     * @pre: nothing
     * @post: nothing
     * @return: one over the number of common digraphs found in the str, this is
     *          because we want our tests standardized for low scores = better
     */
    float digraph_test(std::string);
    

    /**
     * letter_test_pcs
     * @pre: nothing
     * @post: nothing
     * @return: the Pearson chi-squared test statistic of the string with
     *          respect to the likelihood the string is an english phrase
     */
    float letter_test(std::string);

    /**
     * hdistance
     * @pre: nothing
     * @post: nothing
     * @return: the Hamming distance between the two strings
     */
    uint hdistance(std::string, std::string);
};

#endif