/**
 * buffer.h
 * @author: jacob hegna <jacobhegna@gmail.com>
 * @date: April 2017
 * @comment: a high-level interface for a buffer of bytes
 */

#ifndef __BUFFER_H_
#define __BUFFER_H_

#include <vector>
#include <string>

namespace jhc {

    enum class encoding {
        ASCII,
        HEX,
        B64
    };

    class buffer {
    public:
    
        /**
         * buffer()
         * @pre: nothing
         * @post: nothing
         * @return: N/A
         */
        buffer();

        /**
         * buffer(std::string, jhc::encoding)
         * @pre: nothing
         * @post: the contents of bytes are populated with the decoded data
         * @return: N/A
         */
        buffer(std::string, jhc::encoding);

        /**
         * buffer(std::vector<uint8_t>)
         * @pre: nothing
         * @post: bytes is populated
         * @return: N/A
         */
        buffer(std::vector<uint8_t>);

        /**
         * set(std::string, jhc::encoding)
         * @pre: nothing
         * @post: bytes is populated with the string data
         * @return: void
         */
        void set(std::string, jhc::encoding);

        /**
         * get(jhc::encoding)
         * @pre: bytes is initialized
         * @post: nothing
         * @return: the data encoded as the parameter specified
         */
        std::string get(jhc::encoding) const;

        /**
         * push(uint8_t)
         * @pre: the buffer is initialized
         * @post: the byte parameter is appended to the buffer
         * @return: void
         */
        void push(uint8_t);

        /**
         * push(jhc::buffer)
         * @pre: the buffer is initialized
         * @post: the parameter buffer is appended to this
         * @return: void
         */
        void push(jhc::buffer);

        /**
         * at(uint)
         * @pre: bytes is initialized
         * @post: nothing
         * @return: the byte at that location, if it exists. Otherwise, return 0
         */
        uint8_t at(uint) const;

        /**
         * chunk(uint, uint)
         * @pre: bytes is initialized
         * @post: nothing
         * @return: the specified chunk of pos and len
         */
        jhc::buffer chunk(uint, uint) const;


        /**
         * size()
         * @pre: bytes is initialized
         * @post: nothing
         * @return: the size of the buffer
         */
        uint size() const;

        /**
         * char_to_byte(char)
         * @pre: nothing
         * @post: nothing
         * @return: the byte conversion for the char
         */
        static uint8_t char_to_byte(char);
        
        /**
         * byte_to_char(uint8_T)
         * @pre: nothing
         * @post: nothing
         * @return: the char conversion for the byte
         */
        static char byte_to_char(uint8_t);
    
        /**
         * operator^(const jhc::buffer&)
         * @pre: the bytes of both buffers are initialized and of the same size
         * @post: nothing
         * @return: a fixed xor of the two buffers
         */
        jhc::buffer operator^(const jhc::buffer&) const;

        /**
         * operator^(const char&)
         * @pre: bytes has been initialized
         * @post: nothing
         * @return: a single-byte xor of the buffer
         */
        jhc::buffer operator^(const char&) const;

    private:
        static const char b64_table[64];

        // the raw byte vector of the buffer
        std::vector<uint8_t> bytes;

        // base64 encoding and decoding taken from here
        // http://stackoverflow.com/questions/342409/how-do-i-base64-encode-decode-in-c

        /**
         * set_as_[ENCODING](std::string)
         * @pre: nothing
         * @post: bytes is populated with the contents of the parameter
         * @return: void
         */
        void set_as_ascii(std::string);
        void set_as_hex(std::string);
        void set_as_b64(std::string);

        /**
         * get_as_[ENCODING](std::string)
         * @pre: bytes is initialized
         * @post: nothing
         * @return: the contents of bytes as formatted as the specified encoding
         */
        std::string get_as_ascii() const;
        std::string get_as_hex() const;
        std::string get_as_b64() const;

    };
};

#endif