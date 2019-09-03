//
// Created by noahp on 21/08/2019.
//

#ifndef SYSPROG_CODEBUILDER_H

#define SYSPROG_CODEBUILDER_H

#include "../Symtable.h"
#include "../Automat.h"
#include "../lib/Link_List.h"

class CodeBuilder {

public:

    CodeBuilder();
    ~CodeBuilder();

    void makeCode();


private:
    Symtable symtable;
    int label_counter = 1;
    std::fstream stream;

    int size_of(const char *identifier);
    Link_List<Token> getTokensFromWithinBrackets(Link_List<Token> tokens, char bracketOpen, char bracketClose);

    void makeCodeDECL(Link_List<Token> tokens);
    void makeCodeDECLS(Link_List<Token> tokens);
    void makeCodeSTATEMENTS(Link_List<Token> tokens);
    void makeCodeSTATEMENT(Link_List<Token> tokens);
    void makeCodeEXP(Link_List<Token> tokens);
    void makeCodeEXP2(Link_List<Token> tokens);
    void makeCodeINDEX(Link_List<Token> tokens);
    void makeCodeOP_EXP(Link_List<Token> tokens);
    void makeCodeOP(Token token);
};


#endif //SYSPROG_CODEBUILDER_H
