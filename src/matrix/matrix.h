#ifndef __MATRIX_H_
#define __MATRIX_H_

#include <vector>

#include "matrix_error.h"

using uint = unsigned int;

namespace jhc {
    template<typename T>
    class matrix {
    public:
        matrix(uint, uint);

        T              get(uint, uint) const throw(jhc::matrix_error);
        std::vector<T> get_col(uint)   const throw(jhc::matrix_error);
        std::vector<T> get_row(uint)   const throw(jhc::matrix_error);

        void set(uint, uint, T)              throw(jhc::matrix_error);

        jhc::matrix<T> operator*(const jhc::matrix<T>& rhs) const;
        jhc::matrix<T> operator+(const jhc::matrix<T>& rhs) const;
    private:
        uint rows, cols;
        std::vector<T> data;
    };
};

#include "matrix.impl"

#endif