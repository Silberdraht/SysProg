//
// Created by noahp on 21/08/2019.
//

#ifndef SYSPROG_CODEBUILDER_H

#define SYSPROG_CODEBUILDER_H

#include "../Symtable.h"
#include "../Automat.h"
#include "../lib/Link_List.h"
#include "../AST/ASTNode.h"
#include "../AST/ASTBuild/ASTCreator.h"

class CodeBuilder {

public:

    CodeBuilder(ASTCreator astCreator, Symtable symTable);
    ~CodeBuilder();

    void makeCode();

private:
    int label_counter = 1;
    std::ofstream stream;

    ASTCreator astCreator;
    Symtable symtable;

    //const char* spaceOrLineBreak = " ";
    const char* file_out = (char*) R"(../parser/output.txt)";

    void makeCodePROG(Link_List<std::shared_ptr<ASTNode>> nodes);
    void makeCodeDECL(Link_List<std::shared_ptr<ASTNode>> nodes);
    void makeCodeDECLS(Link_List<std::shared_ptr<ASTNode>> nodes);
    void makeCodeARRAY(Link_List<std::shared_ptr<ASTNode>> nodes);
    void makeCodeSTATEMENTS(Link_List<std::shared_ptr<ASTNode>> tokens);
    void makeCodeSTATEMENT(Link_List<std::shared_ptr<ASTNode>> nodes);
    void makeCodeEXP(Link_List<std::shared_ptr<ASTNode>> nodes);
    void makeCodeEXP2(Link_List<std::shared_ptr<ASTNode>> nodes);
    void makeCodeINDEX(Link_List<std::shared_ptr<ASTNode>> nodes);
    void makeCodeOP_EXP(Link_List<std::shared_ptr<ASTNode>> nodes);
    void makeCodeOP(std::shared_ptr<ASTNode> node);
};


#endif //SYSPROG_CODEBUILDER_H
