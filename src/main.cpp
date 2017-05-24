#include <iostream>
#include <fstream>
#include <tuple>

#include "buffer.h"
#include "analysis.h"
#include "xor.h"

#include "matrix/matrix.h"
#include "AES/AES.h"

std::string read_file(std::ifstream& file) {
    std::string line, ret;
    while(std::getline(file, line)) {
        ret += line;
    }
    return ret;
}

int main(int argc, char *argv[]) {
    std::ifstream file("test/1_7.txt");
    jhc::buffer buf(read_file(file), jhc::encoding::HEX);
    jhc::buffer key("YELLOW SUBMARINE", jhc::encoding::ASCII);

    auto output = jhc::AES::encrypt_block(buf.chunk(0, 16), key, jhc::AES::Mode::AES_128);

    return 0;
}

