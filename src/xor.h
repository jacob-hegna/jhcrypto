/**
 * xor.h
 * @author: jacob hegna <jacobhegna@gmail.com>
 * @date: April 2017
 * @comment: a collection of functions to assist with xor-based cryptography
 */

#ifndef __XOR_H_
#define __XOR_H_

#include <tuple>
#include <algorithm>
#include <functional>
#include <string>

#include "buffer.h"
#include "analysis.h"

namespace jhc {

    /**
     * encrypt_repeating_xor(std::buffer, jhc::buffer)
     * @pre: nothing
     * @post: nothing
     * @return: the encrypted buffer, encrypted using repeating-key xor
     */
    jhc::buffer encrypt_xor_repeating(jhc::buffer, jhc::buffer);

    /**
     * break_xor_repeating(std::buffer)
     * @pre: nothing
     * @post: nothing
     * @return: the attempted broken buffer and the key
     */
    std::tuple<jhc::buffer, jhc::buffer> break_xor_repeating(jhc::buffer);

    /**
     * break_xor_single(jhc::buffer, std::function<float(std::string)>)
     * @pre: nothing
     * @post: nothing
     * @return: the attempted broken buffer and the key
     */
    std::tuple<jhc::buffer, jhc::buffer> break_xor_single(jhc::buffer, std::function<float(std::string)>);

};

#endif