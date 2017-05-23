#ifndef __MATRIX_ERROR_H_
#define __MATRIX_ERROR_H_

#include <stdexcept>
#include <string>

namespace jhc {
    class matrix_error : public std::logic_error {
    public:
        /**
         * matrix_error(const std::string&)
         * @pre: nothing
         * @post: an exception passed up the exception chain
         * @return: N/A
         */
        matrix_error(const std::string& msg = "");
    };
};

#endif