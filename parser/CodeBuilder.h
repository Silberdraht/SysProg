//
// Created by noahp on 21/08/2019.
//

#ifndef SYSPROG_CODEBUILDER_H

#define SYSPROG_CODEBUILDER_H

#include "Link_List.h"
#include "../Symtable.h"
#include "../Automat.h"

class CodeBuilder {

public:



private:
    Symtable symtable;
    int labelcounter = 1;

    int size_of(char *identifier);
    Link_List getTokensFromWithinBrackets(Link_List<Token> tokens, char bracketOpen, char bracketClose);

    char* makeCodeDECL(Link_List tokens);
    char* makeCodeDECLS(Link_List tokens);
    char* makeCodeSTATEMENTS(Link_List tokens);
    char* makeCodeSTATEMENT(Link_List tokens);
    char* makeCodeEXP(Link_List tokens);
    char* makeCodeEXP2(Link_List tokens);
    char* makeCodeINDEX(Link_List tokens);
    char* makeCodeOP_EXP(Link_List tokens);
    char* makeCodeOP(Token token);
};


#endif //SYSPROG_CODEBUILDER_H
