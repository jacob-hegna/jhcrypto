#include "AES_error.h"

jhc::AES::AES_error::AES_error(const std::string& msg)
    : std::logic_error(msg)
    {}