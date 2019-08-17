//
// Created by Nil on 17.08.2019.
//

#include <bits/shared_ptr.h>
#include "generateasb.h"
#include "../TokenList.h"

std::unique_ptr<char> generateasb::generate(std::shared_ptr<TokenList> token) {
    switch (token->popToken().tokenType) {
        case 0:
            return sign_token();
        case 1:
            return  digit_token();
        case 2:
            return  identifier_token();
        case 3:
            return error_token();
        case 4:
            return if_token();
        case 5:
            return while_token();
        case 6:
            return else_token();
        case 7:
            return int_token();
        case 8:
            return read_token();
        case 9:
            return write_token();
        default:
            //TODO
            throw;
    }
}

std::unique_ptr<char> generateasb::sign_token() {
    return std::unique_ptr<char>();
}

std::unique_ptr<char> generateasb::digit_token() {
    return std::unique_ptr<char>();
}

std::unique_ptr<char> generateasb::identifier_token() {
    return std::unique_ptr<char>();
}

std::unique_ptr<char> generateasb::error_token() {
    return std::unique_ptr<char>();
}

std::unique_ptr<char> generateasb::if_token() {

    return std::unique_ptr<char>();
}

std::unique_ptr<char> generateasb::while_token() {
    return std::unique_ptr<char>();
}

std::unique_ptr<char> generateasb::else_token() {
    return std::unique_ptr<char>();
}

std::unique_ptr<char> generateasb::int_token() {
    return std::unique_ptr<char>();
}

std::unique_ptr<char> generateasb::read_token() {
    return std::unique_ptr<char>();
}

std::unique_ptr<char> generateasb::write_token() {
    return std::unique_ptr<char>();
}
