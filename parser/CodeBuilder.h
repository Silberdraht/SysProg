//
// Created by noahp on 21/08/2019.
//

#ifndef SYSPROG_CODEBUILDER_H

#define SYSPROG_CODEBUILDER_H

#include "../Symtable.h"
#include "../Automat.h"
#include "../lib/Link_List.h"
#include "../AST/ASTNode.h"

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

    void makeCodeDECL(Link_List<ASTNode> nodes);
    void makeCodeDECLS(Link_List<ASTNode> nodes);
    void makeCodeSTATEMENTS(Link_List<ASTNode> tokens);
    void makeCodeSTATEMENT(Link_List<ASTNode> nodes);
    void makeCodeEXP(Link_List<ASTNode> nodes);
    void makeCodeEXP2(Link_List<ASTNode> nodes);
    void makeCodeINDEX(Link_List<ASTNode> nodes);
    void makeCodeOP_EXP(Link_List<ASTNode> nodes);
    void makeCodeOP(ASTNode node);
};


#endif //SYSPROG_CODEBUILDER_H
