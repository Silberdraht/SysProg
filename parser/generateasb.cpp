//
// Created by Nil on 17.08.2019.
//


#include "generateasb.h"
#include "../TokenList.h"
#include "../Automat.h"


std::unique_ptr<char> generateasb::generate(std::shared_ptr<TokenList> token) {
    switch ((int) token.get()->popToken().tokenType) {
        case 0:
            return sign_token();
        case 1:
            return  digit_token();
        case 2:
            return  identifier_token();
        case 3:
            return error_token();
        case 4:
            return if_token(token.operator*());
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

std::unique_ptr<char> generateasb::if_token(TokenList &token) {
    std::string result;
    Token bufferedToken;
    bool useBufferedToken = 0;

    while (!token.isEmpty()) {

        Token actual_token = token.popToken();
        if (actual_token.tokenType == TokenType::IdentifierToken) {
            Token checkForBracket = token.getToken(0);
            if (checkForBracket.tokenType == TokenType::SignToken && symtable.lookup(checkForBracket.storage.key).getLexem()[0] == '[') {
                token.popToken();
                long offset = token.popToken().storage.number;
                //"LA $" + varblenname+offset
            } else {
                //"LA $" + variablenname
            }

            if (useBufferedToken && bufferedToken.tokenType == TokenType::SignToken) {
                useBufferedToken = 0;
                getOperationForSign(bufferedToken);
            }
        }

        else if (actual_token.tokenType == TokenType::DigitToken){
            //LC konstante hierher
            if (useBufferedToken && bufferedToken.tokenType == TokenType::SignToken) {
                useBufferedToken = 0;
                getOperationForSign(bufferedToken);
            }

        }

        else if (actual_token.tokenType == TokenType::SignToken){
            char *sign = symtable.lookup(actual_token.storage.key).getLexem();
            if (sign[0] == '>'){
                //LES
                //JIN L1
            }
            else if (sign[0] == '<'){
               //LES
               //NOT
               //JIN L1
            }
            else if (sign[0] == '='){
                //EQU
                //NOT
                //JIN L1
            }
            else if (sign[0] == '+' || sign[0] == '-' || sign[0] == '*' || sign[0] == ':') {
                bufferedToken = actual_token;
                useBufferedToken = 1;
            }  //sign ']' can simply be ignored. syntactical correctness should have been checked previously

        }
    }

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

/** Hilfsfunktionen **/

std::unique_ptr<char> generateasb::getOperationForSign(Token token) {
    std::unique_ptr<char> result;
    char *sign = symtable.lookup(token.storage.key).getLexem();
    if (sign[0] == '+') {
        //ADD
    } else if (sign[0] == '-') {
        //SUB
    } else if (sign[0] == '*') {
        //MUL
    } else if (sign[0] == ':') {
        //DIV
    }
    return result;
}

