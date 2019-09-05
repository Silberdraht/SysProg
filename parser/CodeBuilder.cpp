//
// Created by noahp on 21/08/2019.
//

#include <fstream>
#include "../lib/Link_List.h"
#include "CodeBuilder.h"

CodeBuilder::CodeBuilder(){
    stream.open(R"(../xxx.code)");
}
CodeBuilder::~CodeBuilder() {
    stream.close();
}

//enum NodeType{
//    // nichtterminale knoten
//            PROG,
//    DECLS,
//    DECL,
//    ARRAY,
//    STATEMENTS,
//    STATEMENT,
//    EXP,
//    EXP2,
//    INDEX,
//    OP_EXP,
//    OP,
//
//    // terminale zeichen
//            PLUSSIGN, 		//+
//    MINUSSIGN,		//-
//    STARSIGN,		//*
//    DOUBLESIGN,	//:
//    LESSSIGN,		//<
//    GREATERSIGN,	//>
//    EQUALSSIGN,	//=
//    OTHEREQUALSSIGN,//:=
//    EQUPEQUSIGN,	//=:=
//    ANDSIGN,		//&&
//    COLONSIGN,		//;
//    EXCLSIGN,		//!
//    // terminale
//            IFSIGN,
//    ELSESIGN,
//    WHILESIGN,
//    READSIGN,
//    WRITESIGN,
//    INTSIGN,
//    // konstanten/ bezeichner
//            IDENTIFIER,
//    INTEGER,
//    // klammern
//            KL_OPEN,	//(
//    KL_CLOSE,
//    EKL_OPEN,	//[
//    EKL_CLOSE,
//    GKL_OPEN,	//{
//    GKL_CLOSE
//
//};

void CodeBuilder::makeCodeDECLS(Link_List<ASTNode> nodes) {
    if (nodes.empty()) {
        return;
    }
    while (!nodes.empty()) {
        ASTNode node = nodes.pop_front();
        if (node.getType() == DECLS) {
            makeCodeDECLS(node.getSubtree());
        } else if (node.getType() == DECL) {
            makeCodeDECL(node.getSubtree());
        }
    }

}


void CodeBuilder::makeCodeDECL(Link_List<ASTNode> nodes) {
    if (nodes.size() == 3) {
        nodes.pop_front();
        Link_List<ASTNode> array = nodes.pop_front().getSubtree();
        int size = -1;
        while (!array.empty()) {
            ASTNode child = array.pop_front();
            if (child.getType() == INTEGER) {
                size = child.getDigit();
            }
        }
        char* identifier = symtable.lookup(nodes.pop_front().getKey()).getLexem();
        stream << "DS " << identifier << " " << size;
    }

}

void CodeBuilder::makeCodeSTATEMENTS(Link_List<ASTNode> nodes) {
    if (nodes.empty()) {
        return;
    }
    if (nodes.empty()) {
        return;
    }
    while (!nodes.empty()) {
        ASTNode node = nodes.pop_front();
        if (node.getType() == STATEMENTS) {
            makeCodeSTATEMENTS(node.getSubtree());
        } else if (node.getType() == STATEMENT) {
            makeCodeSTATEMENT(node.getSubtree());
        }
    }

}

void CodeBuilder::makeCodeSTATEMENT(Link_List<ASTNode> nodes) {

    ASTNode node = nodes.pop_front();

    if (node.getType() == IFSIGN) {
        Link_List<ASTNode> exp;
        Link_List<ASTNode> statement1;
        Link_List<ASTNode> statement2;
        bool stmt1Used = false;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node.getType() == EXP) {
                exp = node.getSubtree();
            } else if (node.getType() == STATEMENT) {
                if (!stmt1Used) {
                    statement2 = node.getSubtree();
                    stmt1Used = true;
                } else {
                    statement1 = node.getSubtree();
                }
            }
        }

        int label1 = label_counter;
        label_counter++;
        int label2 = label_counter;
        label_counter++;
        makeCodeEXP(exp);
        stream << "JIN #LABEL" << label1 << " ";
        makeCodeSTATEMENT(statement1);
        stream << "JMP #LABEL" << label2 << " ";
        stream << "#LABEL" << label1 << " NOP ";
        makeCodeSTATEMENT(statement2);

    }

    else if (node.getType() == WHILESIGN) {
        Link_List<ASTNode> exp;
        Link_List<ASTNode> statement;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node.getType() == EXP) {
                exp = node.getSubtree();
            } else if (node.getType() == STATEMENT) {
                statement = node.getSubtree();
            }
        }

        int label1 = label_counter;
        label_counter++;
        int label2 = label_counter;
        label_counter++;
        stream << "#LABEL" << label1 << " NOP ";
        makeCodeEXP(exp);
        stream << "JIN #LABEL" << label2 << " ";
        makeCodeSTATEMENT(statement);
        stream << "JMP #LABEL" << label1 << " ";
        stream << "#LABEL" << label2 << " NOP ";
    }

    else if (node.getType() == WRITESIGN) {
        Link_List<ASTNode> exp;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node.getType() == EXP) {
                exp = node.getSubtree();
            }
        }
        makeCodeEXP(exp);
        stream << "PRI ";
    }

    else if (node.getType() == READSIGN) {
        Key identifierKey{};
        bool visited = false;
        Link_List<ASTNode> index;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node.getType() == IDENTIFIER) {
                identifierKey = node.getKey();
                visited = true;
            } else if (node.getType() == INDEX) {
                index = node.getSubtree();
            }
        }
        if (visited) {
            char* identifier = symtable.lookup(identifierKey).getLexem();
            stream << "REA ";
            stream << "LA $" << identifier << " ";
            makeCodeINDEX(index);
            stream << "STR ";
        }

    }

    else if (node.getType() == IDENTIFIER) {
        char* identifier = symtable.lookup(node.getKey()).getLexem();
        Link_List<ASTNode> index;
        Link_List<ASTNode> exp;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node.getType() == INDEX) {
                index = node.getSubtree();
            } else if (node.getType() == EXP) {
                exp = node.getSubtree();
            }
        }
        makeCodeEXP(exp);
        stream << "LA $" << identifier << " ";
        makeCodeINDEX(index);
        stream << "STR ";
    }

    else if (node.getType() == GKL_OPEN) { //{
        Link_List<ASTNode> stmts;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node.getType() == STATEMENTS) {
                stmts = node.getSubtree();
            }
        }
        makeCodeSTATEMENTS(stmts);
    }

}


void CodeBuilder::makeCodeEXP(Link_List<ASTNode> nodes) { //TODO check for idiocy
    ASTNode exp2;
    ASTNode op_exp;
    while (!nodes.empty()) {
        ASTNode node = nodes.pop_front();
        if (node.getType() == EXP2) {
            exp2 = node;
        } else if (node.getType() == OP_EXP) {
            op_exp = node;
        }
    }
    NodeType opType = op_exp.getSubtree().front().getSubtree().front().getType();
    if (opType == GREATERSIGN) {
        makeCodeEXP(op_exp.getSubtree().pop_back().getSubtree());
        op_exp.getSubtree().push_back(exp2);
    }
    makeCodeEXP2(exp2.getSubtree());
    makeCodeOP_EXP(op_exp.getSubtree());
    if (opType == EQUPEQUSIGN) {
        stream << "NOT ";
    }

}

void CodeBuilder::makeCodeEXP2(Link_List<ASTNode> nodes) {
    ASTNode node = nodes.pop_front();
    if (node.getType() == IDENTIFIER) {
        char* identifier = symtable.lookup(node.getKey()).getLexem();
        Link_List<ASTNode> index;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node.getType() == INDEX) {
                index = node.getSubtree();
            }
        }
        stream << "LA $" << identifier << " ";
        makeCodeINDEX(index);
        stream << "LV ";
    }
    else if (node.getType() == INTSIGN) {
        int integer = (int) node.getDigit();
        stream << "LC " << integer << " ";
    }
    else if (node.getType() == MINUSSIGN) {
        Link_List<ASTNode> exp2;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node.getType() == EXP2) {
                exp2 = node.getSubtree();
            }
        }
        stream << "LC 0 ";
        makeCodeEXP2(exp2);
        stream << "SUB ";

    }
    else if (node.getType() == EXCLSIGN) {
        stream << "NOT ";
    }
    else if (node.getType() == KL_OPEN) {
        Link_List<ASTNode> exp;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node.getType() == EXP) {
                exp = node.getSubtree();
            }
        }
        makeCodeEXP(exp);
    }

}

void CodeBuilder::makeCodeOP_EXP(Link_List<ASTNode> nodes) {
    Link_List<ASTNode> op;
    Link_List<ASTNode> exp;
    bool isExp2 = false;
    while (!nodes.empty()) {
        ASTNode node = nodes.pop_front();
        if (node.getType() == OP) {
            op = node.getSubtree();
        } else if (node.getType() == EXP) {
            exp = node.getSubtree();
        } else if (node.getType() == EXP2) {
            isExp2 = true;
            exp = node.getSubtree();
        } else {
            op.push_front(node); //directly contained operand

        }
    }
    if (isExp2) {
        makeCodeEXP2(exp);
    } else {
        makeCodeEXP(exp);
    }
    makeCodeOP(op.pop_front());
}

void CodeBuilder::makeCodeINDEX(Link_List<ASTNode> nodes) {
    nodes.pop_front();
    nodes.pop_back();
    if (!nodes.empty()) {
        makeCodeEXP(nodes);
        stream << "ADD ";
        //ADD
    } else {
        //return (char *) "";
    }

}


void CodeBuilder::makeCodeOP(ASTNode node) {
    char* result;
    char *sign = symtable.lookup(node.getKey()).getLexem();
    char c = sign[0];
    if (c == '+') {
        result = (char *) "ADD ";
    } else if (c == '-') {
        result = (char *) "SUB ";
    } else if (c == '*') {
        result = (char *) "MUL ";
    } else if (c == ':') {
        result = (char *) "DIV ";
    } else if (c == '=') {
        result = (char *) "EQU ";
    } else if (c == '<') {
        result = (char *) "LES ";
    } else if (c == '&' ) {
        result = (char *) "AND ";
    } else {
        result = (char *) "NOP "; //should never be reached by valid code
    }
    stream << result;
}


Link_List<Token> CodeBuilder::getTokensFromWithinBrackets(Link_List<Token> tokens, char bracketOpen, char bracketClose) { //iput Link_List "tokens" should be modified in place
    Link_List<Token> withinBrackets;
    tokens.pop_front();
    int bracketsOpen = 1;
    int bracketsClose = 0;
    while (bracketsOpen > bracketsClose) {
        Token token = tokens.pop_front();
        if (token.tokenType == SignToken) {
            if (symtable.lookup(token.storage.key).getLexem()[0] == bracketOpen) {
                bracketsOpen++;
            } else if (symtable.lookup(token.storage.key).getLexem()[0] == bracketClose) {
                bracketsClose++;
            }
        }
        withinBrackets.push_back(token);
    }
    withinBrackets.pop_back();
    return withinBrackets;
}


int CodeBuilder::size_of(const char *identifier) {
    int index = 0;
    while (identifier[index] != '\0') {
        index++;
    }
    return index;
}

void CodeBuilder::makeCode() {

}





//enum TokenType {
//    SignToken = 0,
//    DigitToken = 1,
//    IdentifierToken = 2,
//    ErrorToken = 3,
//    IfToken = 4,
//    WhileToken = 5,
//    ElseToken = 6,
//    IntToken = 7,
//    ReadToken = 8,
//    WriteToken = 9
//};