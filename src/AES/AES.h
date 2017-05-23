#ifndef __AES_H_
#define __AES_H_

#include "AES_error.h"

#include "../buffer.h"
#include "../matrix/matrix.h"

namespace jhc { namespace AES {
    enum class Mode {
        AES_128,
        AES_192,
        AES_256
    };

    jhc::buffer encrypt_block(jhc::buffer, jhc::buffer, jhc::AES::Mode);
    jhc::matrix<uint8_t> sub_bytes(jhc::matrix<uint8_t>);
    jhc::matrix<uint8_t> shift_rows(jhc::matrix<uint8_t>);
    jhc::matrix<uint8_t> mix_cols(jhc::matrix<uint8_t>);
}};

#endif