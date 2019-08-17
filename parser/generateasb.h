//
// Created by Nil on 17.08.2019.
//

#ifndef SYSPROG_GENERATEASB_H
#define SYSPROG_GENERATEASB_H

#include <memory>
#include "Node.h"

class generateasb {
public:
    std::unique_ptr<char> generate(std::shared_ptr<TokenList> token);
    Symtable symtable;
private:
    enum node_type {

    };
    std::unique_ptr<char>  sign_token();
    std::unique_ptr<char>  digit_token();
    std::unique_ptr<char>  identifier_token();
    std::unique_ptr<char>  error_token();
    std::unique_ptr<char>  if_token(TokenList &token);
    std::unique_ptr<char>  while_token();
    std::unique_ptr<char>  else_token();
    std::unique_ptr<char>  int_token();
    std::unique_ptr<char>  read_token();
    std::unique_ptr<char>  write_token();

};


#endif //SYSPROG_GENERATEASB_H
