/**
 * buffer.cpp
 * @author: jacob hegna <jacobhegna@gmail.com>
 * @date: April 2017
 * @comment: a high-level interface for a buffer of bytes
 */

#include "buffer.h"

const char jhc::buffer::b64_table[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
};

/**************************
******* CONSTRUCTORS ******
**************************/

jhc::buffer::buffer() {}

jhc::buffer::buffer(std::string str, jhc::encoding encoding) {
    this->set(str, encoding);
}

jhc::buffer::buffer(std::vector<uint8_t> bytes)
    : bytes(bytes)
    {}

/**************************
****** PUBLIC METHODS *****
**************************/

void jhc::buffer::set(std::string data, jhc::encoding encoding) {
    switch(encoding) {
        case jhc::encoding::ASCII: set_as_ascii(data); break;
        case jhc::encoding::HEX:   set_as_hex(data);   break;
        case jhc::encoding::B64:   set_as_b64(data);   break;
    }
}

std::string jhc::buffer::get(jhc::encoding encoding) const {
    switch(encoding) {
        case jhc::encoding::ASCII: return get_as_ascii();
        case jhc::encoding::HEX:   return get_as_hex();
        case jhc::encoding::B64:   return get_as_b64();
    }

    // should never be reached
    return "";
}

void jhc::buffer::push(uint8_t byte) {
    bytes.push_back(byte);
}

void jhc::buffer::push(jhc::buffer buf) {
    bytes.insert(bytes.end(), buf.bytes.begin(), buf.bytes.end());
}

uint8_t jhc::buffer::at(uint loc) const {
    return (loc < bytes.size()) ? bytes.at(loc) : 0;
}

jhc::buffer jhc::buffer::chunk(uint pos, uint len) const {
    return jhc::buffer(
        std::vector<uint8_t>(bytes.begin() + pos, bytes.begin() + pos + len)
    );
}

uint jhc::buffer::size() const {
    return bytes.size();
}

/**************************
****** STATIC METHODS *****
**************************/

uint8_t jhc::buffer::char_to_byte(char c) {
    if(c >= '0' && c <= '9') {
        return c - '0';
    }

    if(c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }

    if(c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }

    return 0;
}

char jhc::buffer::byte_to_char(uint8_t b) {
    if(b >= 0 && b <= 9) {
        return b + '0';
    }

    if(b >= 10 && b <= 15) {
        return b + 'a' - 10;
    }

    return 0;
}

/**************************
**** OPERATOR OVERLOADS ***
**************************/

jhc::buffer jhc::buffer::operator^(const jhc::buffer& rhc) const {
    std::vector<uint8_t> new_bytes;

    if(this->bytes.size() != rhc.bytes.size()) {
        // throw error
    }

    for(uint i = 0; i < this->bytes.size(); ++i) {
        new_bytes.push_back(
            this->bytes.at(i) ^ rhc.bytes.at(i)
        );
    }

    return jhc::buffer(new_bytes);
}

jhc::buffer jhc::buffer::operator^(const char& c) const {
    std::vector<uint8_t> new_bytes;

    for(uint i = 0; i < this->bytes.size(); ++i) {
        new_bytes.push_back(
            this->bytes.at(i) ^ c
        );
    }

    return jhc::buffer(new_bytes);
}

/**************************
***** GETTERS/SETTERS *****
**************************/

void jhc::buffer::set_as_ascii(std::string str) {

    // reset the buffer
    bytes.clear();
    bytes.reserve(str.size());

    for(uint i = 0; i < str.size(); ++i) {
        bytes.push_back(str[i]);
    }
}

void jhc::buffer::set_as_hex(std::string str) {

    // reset the buffer
    bytes.clear();

    // ensure an even number of hex digits
    if(str.size() % 2 == 1) str.insert(0, 1, '0');
    bytes.reserve(str.size() / 2);


    for(uint i = 0; i < str.size(); i += 2) {
        bytes.push_back(0);
        bytes[i/2]  = jhc::buffer::char_to_byte(str[i]) << 4;
        bytes[i/2] |= jhc::buffer::char_to_byte(str[i + 1]);
    }
}

void jhc::buffer::set_as_b64(std::string str) {
    static uint8_t b64_table_decode[256];
    if(b64_table_decode[0] == 0) {
        for(uint i = 0; i < 64; ++i) {
            b64_table_decode[(unsigned char) jhc::buffer::b64_table[i]] = i;
        }
    }

    uint buffer_length = (str.size() / 4) * 3;

    // reset the buffer
    bytes.clear();
    bytes.reserve(buffer_length);

    for(uint i = 0; i < str.size();) {
        uint32_t sextet_a = str[i] == '=' ? 0 & i++ : b64_table_decode[str[i++]];
        uint32_t sextet_b = str[i] == '=' ? 0 & i++ : b64_table_decode[str[i++]];
        uint32_t sextet_c = str[i] == '=' ? 0 & i++ : b64_table_decode[str[i++]];
        uint32_t sextet_d = str[i] == '=' ? 0 & i++ : b64_table_decode[str[i++]];

        uint32_t triple = (sextet_a << 3 * 6)
        + (sextet_b << 2 * 6)
        + (sextet_c << 1 * 6)
        + (sextet_d << 0 * 6);

        if (bytes.size() < buffer_length) bytes.push_back((triple >> 2 * 8) & 0xFF);
        if (bytes.size() < buffer_length) bytes.push_back((triple >> 1 * 8) & 0xFF);
        if (bytes.size() < buffer_length) bytes.push_back((triple >> 0 * 8) & 0xFF);
    }
}

std::string jhc::buffer::get_as_ascii() const {
    return std::string(bytes.begin(), bytes.end());
}

std::string jhc::buffer::get_as_hex() const {
    std::string hexstr;

    for(uint8_t byte : bytes) {
        hexstr += jhc::buffer::byte_to_char(byte >> 4);
        hexstr += jhc::buffer::byte_to_char(byte & 0x0F);
    }

    return hexstr;
}

std::string jhc::buffer::get_as_b64() const {
    std::string b64str;

    for(int i = 0; i < bytes.size();) {
        uint32_t octet_a = (i < bytes.size()) ? bytes[i++] : 0;
        uint32_t octet_b = (i < bytes.size()) ? bytes[i++] : 0;
        uint32_t octet_c = (i < bytes.size()) ? bytes[i++] : 0;

        uint32_t triple  = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        b64str += jhc::buffer::b64_table[(triple >> 3 * 6) & 0x3f];
        b64str += jhc::buffer::b64_table[(triple >> 2 * 6) & 0x3f];
        b64str += jhc::buffer::b64_table[(triple >> 1 * 6) & 0x3f];
        b64str += jhc::buffer::b64_table[(triple >> 0 * 6) & 0x3f];
    }

    return b64str;
}
