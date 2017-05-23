/**
 * xor.cpp
 * @author: jacob hegna <jacobhegna@gmail.com>
 * @date: April 2017
 * @comment: a collection of functions to assist with xor-based cryptography
 */

#include "xor.h"

jhc::buffer jhc::encrypt_xor_repeating(jhc::buffer data, jhc::buffer key) {
    jhc::buffer key_repeating(key);    

    for(uint i = 0; i < data.size(); ++i) {
        key_repeating.push(key.at(i % key.size()));
    }

    return data ^ key_repeating;
}

std::tuple<jhc::buffer, jhc::buffer> jhc::break_xor_repeating(jhc::buffer data) {

    uint best_key_size = 2;
    float best_dist    = 99999;

    std::vector<std::tuple<float, uint>> keys;

    for(uint key_size = 2; key_size <= 40; ++key_size) {
        std::string str_a, str_b, str_c, str_d;

        str_a = data.get(jhc::encoding::ASCII).substr(0,        key_size);
        str_b = data.get(jhc::encoding::ASCII).substr(key_size, key_size);
        str_c = data.get(jhc::encoding::ASCII).substr(key_size, key_size);
        str_d = data.get(jhc::encoding::ASCII).substr(key_size, key_size);

        float dist_ab = hdistance(str_a, str_b);
        float dist_cd = hdistance(str_c, str_d);

        dist_ab /= key_size;
        dist_cd /= key_size;
    
        float dist = (dist_ab + dist_cd) / 2.0;

        keys.emplace_back(dist, key_size);
    }

    std::vector<jhc::buffer> broken_keys;
    for(auto& key : keys) {
        std::vector<jhc::buffer> blocks;
        for(uint i = 0; i < data.size(); i += std::get<1>(key)) {
            blocks.emplace_back(
                data.get(jhc::encoding::ASCII).substr(i, std::get<1>(key)),
                jhc::encoding::ASCII
            );
        }

        std::vector<jhc::buffer> transposed_blocks;
        for(uint i = 0; i < std::get<1>(key); ++i) {
            jhc::buffer buf;
            for(auto block : blocks) {
                buf.push(block.at(i));
            }
            transposed_blocks.push_back(buf);
        }

        jhc::buffer broken_key;
        for(uint i = 0; i < transposed_blocks.size(); ++i) {
            auto single_break = jhc::break_xor_single(transposed_blocks.at(i), jhc::digraph_test);

            broken_key.push(std::get<0>(single_break));
        }

        broken_keys.push_back(broken_key);
    }

    std::vector<std::tuple<float, std::string>> scored_keys;
    for(auto& key : broken_keys) {
        scored_keys.emplace_back(
            digraph_test(encrypt_xor_repeating(data, key).get(jhc::encoding::ASCII)),
            key.get(jhc::encoding::ASCII)
        );
    }

    std::sort(scored_keys.begin(), scored_keys.end());
    
    auto key = jhc::buffer(std::get<1>(scored_keys.at(0)), jhc::encoding::ASCII);

    return std::make_tuple(
        key,
        encrypt_xor_repeating(data, key)
    );
}


std::tuple<jhc::buffer, jhc::buffer> jhc::break_xor_single(jhc::buffer buffer, std::function<float(std::string)> test) {
    std::vector<std::tuple<float, std::string, std::string>> decryptions;

    // iterate through all ascii chars 
    for(char i = 0; i < 126; ++i) {
        std::string str = (buffer ^ i).get(jhc::encoding::ASCII);

        decryptions.emplace_back(
            test(str),
            std::string(1, i),
            str
        );
    }

    // sort in ascending order
    std::sort(decryptions.begin(), decryptions.end());

    // return the lowest scoring key/buffer combination
    return std::make_tuple(
        jhc::buffer(std::get<1>(decryptions.at(0)), jhc::encoding::ASCII),
        jhc::buffer(std::get<2>(decryptions.at(0)), jhc::encoding::ASCII)
    );
}