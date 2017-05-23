#include "matrix_error.h"

jhc::matrix_error::matrix_error(const std::string& msg)
    : std::logic_error(msg)
    {}