//
// Created by noahp on 21/08/2019.
//

#ifndef SYSPROG_CODEBUILDER_H

#define SYSPROG_CODEBUILDER_H

#include "../Symtable.h"
#include "../Automat.h"

class CodeBuilder {

public:



private:
    Symtable symtable;
    int label_counter = 1;

    int size_of(const char *identifier);
    Link_List<Token> getTokensFromWithinBrackets(Link_List<Token> tokens, char bracketOpen, char bracketClose);

    char* makeCodeDECL(Link_List<Token> tokens);
    char* makeCodeDECLS(Link_List<Token> tokens);
    char* makeCodeSTATEMENTS(Link_List<Token> tokens);
    char* makeCodeSTATEMENT(Link_List<Token> tokens);
    char* makeCodeEXP(Link_List<Token> tokens);
    char* makeCodeEXP2(Link_List<Token> tokens);
    char* makeCodeINDEX(Link_List<Token> tokens);
    char* makeCodeOP_EXP(Link_List<Token> tokens);
    char* makeCodeOP(Token token);
};


#endif //SYSPROG_CODEBUILDER_H
