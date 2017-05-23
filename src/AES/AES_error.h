#ifndef __AES_ERROR_H_
#define __AES_ERROR_H_

#include <stdexcept>
#include <string>

namespace jhc { namespace AES {
    class AES_error : public std::logic_error {
    public:
        /**
         * AES_error(const std::string&)
         * @pre: nothing
         * @post: an exception passed up the exception chain
         * @return: N/A
         */
        AES_error(const std::string& msg = "");
    };
}};

#endif