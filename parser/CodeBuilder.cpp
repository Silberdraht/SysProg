//
// Created by noahp on 21/08/2019.
//

#include <fstream>
#include "../lib/Link_List.h"
#include "CodeBuilder.h"

CodeBuilder::CodeBuilder(ASTCreator astCreator, Symtable symTable) : astCreator(astCreator), symtable(symTable) {
}
CodeBuilder::~CodeBuilder() {
}

void CodeBuilder::makeCodeDECLS(Link_List<std::shared_ptr<ASTNode>> nodes) {
    while (!nodes.empty()) {
        std::shared_ptr<ASTNode> node = nodes.pop_front();
        if (node->getType() == DECLS) {
            makeCodeDECLS(node->getSubtree());
        } else if (node->getType() == DECL) {
            makeCodeDECL(node->getSubtree());
        }
    }

}


void CodeBuilder::makeCodeDECL(Link_List<std::shared_ptr<ASTNode>> nodes) {
    Link_List<std::shared_ptr<ASTNode>> array;
    char* identifier;
    while(!nodes.empty()) {
        std::shared_ptr<ASTNode> node = nodes.pop_front();
        if (node->getType() == IDENTIFIER) {
            identifier = symtable.lookup(node->getKey()).getLexem();
        } else if (node->getType() == ARRAY) {
            array = node->getSubtree();
        }
    }
    stream.open(file_out, std::fstream::app);
    stream << "DS " << identifier << " ";
    stream.close();
    makeCodeARRAY(array);
}

void CodeBuilder::makeCodeARRAY(Link_List<std::shared_ptr<ASTNode>> nodes) {
    int size = -1;
    while (!nodes.empty()) {
        std::shared_ptr<ASTNode> arrayNode = nodes.pop_front();
        if (arrayNode->getType() == INTEGER) {
            size = arrayNode->getDigit();
        }
    }
    if (size == -1) {
        size = 1;
    }
    stream.open(file_out, std::fstream::app);
    stream << size << " ";
    stream.close();
}

void CodeBuilder::makeCodeSTATEMENTS(Link_List<std::shared_ptr<ASTNode>> nodes) {
    while (!nodes.empty()) {
        std::shared_ptr<ASTNode> node = nodes.pop_front();
        if (node->getType() == STATEMENTS) {
            makeCodeSTATEMENTS(node->getSubtree());
        } else if (node->getType() == STATEMENT) {
            makeCodeSTATEMENT(node->getSubtree());
        }
    }

}

void CodeBuilder::makeCodeSTATEMENT(Link_List<std::shared_ptr<ASTNode>> nodes) {

    std::shared_ptr<ASTNode> node = nodes.pop_front();

    if (node->getType() == IFSIGN) {
        Link_List<std::shared_ptr<ASTNode>> exp;
        Link_List<std::shared_ptr<ASTNode>> statement1;
        Link_List<std::shared_ptr<ASTNode>> statement2;
        bool stmt1Used = false;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node->getType() == EXP) {
                exp = node->getSubtree();
            } else if (node->getType() == STATEMENT) {
                if (!stmt1Used) {
                    statement2 = node->getSubtree();
                    stmt1Used = true;
                } else {
                    statement1 = node->getSubtree();
                }
            }
        }

        int label1 = label_counter;
        label_counter++;
        int label2 = label_counter;
        label_counter++;
        makeCodeEXP(exp);
        stream.open(file_out, std::fstream::app);
        stream << "JIN #LABEL" << label1 << " ";
        stream.close();
        makeCodeSTATEMENT(statement1);
        stream.open(file_out, std::fstream::app);
        stream << "JMP #LABEL" << label2 << " ";
        stream << "#LABEL" << label1 << " NOP ";
        stream.close();
        makeCodeSTATEMENT(statement2);
    }

    else if (node->getType() == WHILESIGN) {
        Link_List<std::shared_ptr<ASTNode>> exp;
        Link_List<std::shared_ptr<ASTNode>> statement;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node->getType() == EXP) {
                exp = node->getSubtree();
            } else if (node->getType() == STATEMENT) {
                statement = node->getSubtree();
            }
        }

        int label1 = label_counter;
        label_counter++;
        int label2 = label_counter;
        label_counter++;
        stream.open(file_out, std::fstream::app);
        stream << "#LABEL" << label1 << " NOP ";
        stream.close();
        makeCodeEXP(exp);
        stream.open(file_out, std::fstream::app);
        stream << "JIN #LABEL" << label2 << " ";
        stream.close();
        makeCodeSTATEMENT(statement);
        stream.open(file_out, std::fstream::app);
        stream << "JMP #LABEL" << label1 << " ";
        stream << "#LABEL" << label2 << " NOP ";
        stream.close();
    }

    else if (node->getType() == WRITESIGN) {
        Link_List<std::shared_ptr<ASTNode>> exp;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node->getType() == EXP) {
                exp = node->getSubtree();
            }
        }
        makeCodeEXP(exp);
        stream.open(file_out, std::fstream::app);
        stream << "PRI ";
        stream.close();
    }

    else if (node->getType() == READSIGN) {
        Key identifierKey{};
        bool visited = false;
        Link_List<std::shared_ptr<ASTNode>> index;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node->getType() == IDENTIFIER) {
                identifierKey = node->getKey();
                visited = true;
            } else if (node->getType() == INDEX) {
                index = node->getSubtree();
            }
        }
        if (visited) {
            char* identifier = symtable.lookup(identifierKey).getLexem();
            stream.open(file_out, std::fstream::app);
            stream << "REA ";
            stream << "LA $" << identifier << " ";
            stream.close();
            makeCodeINDEX(index);
            stream.open(file_out, std::fstream::app);
            stream << "STR ";
            stream.close();
        }
    }

    else if (node->getType() == IDENTIFIER) {
        char* identifier = symtable.lookup(node->getKey()).getLexem();
        Link_List<std::shared_ptr<ASTNode>> index;
        Link_List<std::shared_ptr<ASTNode>> exp;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node->getType() == INDEX) {
                index = node->getSubtree();
            } else if (node->getType() == EXP) {
                exp = node->getSubtree();
            }
        }
        makeCodeEXP(exp);
        stream.open(file_out, std::fstream::app);
        stream << "LA $" << identifier << " ";
        stream.close();
        makeCodeINDEX(index);
        stream.open(file_out, std::fstream::app);
        stream << "STR ";
        stream.close();
    }

    else if (node->getType() == GKL_OPEN) { //{
        Link_List<std::shared_ptr<ASTNode>> stmts;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node->getType() == STATEMENTS) {
                stmts = node->getSubtree();
            }
        }
        makeCodeSTATEMENTS(stmts);
    }
}


void CodeBuilder::makeCodeEXP(Link_List<std::shared_ptr<ASTNode>> nodes) {
    std::shared_ptr<ASTNode> exp2;
    std::shared_ptr<ASTNode> op_exp;
    while (!nodes.empty()) {
        std::shared_ptr<ASTNode> node = nodes.pop_front();
        if (node->getType() == EXP2) {
            exp2 = node;
        } else if (node->getType() == OP_EXP) {
            op_exp = node;
        }
    }
    NodeType opType = op_exp->getSubtree().front()->getSubtree().front()->getType(); //SEGFAULT
    if (opType == GREATERSIGN) {
        makeCodeEXP(op_exp->getSubtree().pop_back()->getSubtree());
        op_exp->getSubtree().push_back(exp2);
    }
    makeCodeEXP2(exp2->getSubtree());
    makeCodeOP_EXP(op_exp->getSubtree());
    if (opType == EQUPEQUSIGN) {
        stream.open(file_out, std::fstream::app);
        stream << "NOT ";
        stream.close();
    }

}

void CodeBuilder::makeCodeEXP2(Link_List<std::shared_ptr<ASTNode>> nodes) {
    std::shared_ptr<ASTNode> node = nodes.pop_front();
    if (node->getType() == IDENTIFIER) {
        char* identifier = symtable.lookup(node->getKey()).getLexem();
        Link_List<std::shared_ptr<ASTNode>> index;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node->getType() == INDEX) {
                index = node->getSubtree();
            }
        }
        stream.open(file_out, std::fstream::app);
        stream << "LA $" << identifier << " ";
        stream.close();
        makeCodeINDEX(index);
        stream.open(file_out, std::fstream::app);
        stream << "LV ";
        stream.close();
    }
    else if (node->getType() == INTEGER) {
        int integer = (int) node->getDigit();
        stream.open(file_out, std::fstream::app);
        stream << "LC " << integer << " ";
        stream.close();
    }
    else if (node->getType() == MINUSSIGN) {
        Link_List<std::shared_ptr<ASTNode>> exp2;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node->getType() == EXP2) {
                exp2 = node->getSubtree();
            }
        }
        stream.open(file_out, std::fstream::app);
        stream << "LC 0 ";
        stream.close();
        makeCodeEXP2(exp2);
        stream.open(file_out, std::fstream::app);
        stream << "SUB ";
        stream.close();

    }
    else if (node->getType() == EXCLSIGN) {
        stream.open(file_out, std::fstream::app);
        stream << "NOT ";
        stream.close();
    }
    else if (node->getType() == KL_OPEN) {
        Link_List<std::shared_ptr<ASTNode>> exp;
        while (!nodes.empty()) {
            node = nodes.pop_front();
            if (node->getType() == EXP) {
                exp = node->getSubtree();
            }
        }
        makeCodeEXP(exp);
    }

}

void CodeBuilder::makeCodeOP_EXP(Link_List<std::shared_ptr<ASTNode>> nodes) {
    Link_List<std::shared_ptr<ASTNode>> op;
    Link_List<std::shared_ptr<ASTNode>> exp;
    bool isExp2 = false;
    while (!nodes.empty()) {
        std::shared_ptr<ASTNode> node = nodes.pop_front();
        if (node->getType() == OP) {
            op = node->getSubtree();
        } else if (node->getType() == EXP) {
            exp = node->getSubtree();
        } else if (node->getType() == EXP2) {
            isExp2 = true;
            exp = node->getSubtree();
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

void CodeBuilder::makeCodeINDEX(Link_List<std::shared_ptr<ASTNode>> nodes) {
    Link_List<std::shared_ptr<ASTNode>> exp;
    while (!nodes.empty()) {
        std::shared_ptr<ASTNode> node = nodes.pop_front();
        if (node->getType() == EXP) {
            exp = node->getSubtree();
        }
    }
    makeCodeEXP(exp);
    stream.open(file_out, std::fstream::app);
    stream << "ADD ";
    stream.close();
}


void CodeBuilder::makeCodeOP(std::shared_ptr<ASTNode> node) {
    char* result;
    char *sign = symtable.lookup(node->getKey()).getLexem();
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
    stream.open(file_out, std::fstream::app);
    stream << result;
    stream.close();
}

void CodeBuilder::makeCodePROG(Link_List<std::shared_ptr<ASTNode>> nodes) {
    Link_List<std::shared_ptr<ASTNode>> decls;
    Link_List<std::shared_ptr<ASTNode>> stmts;
    while (!nodes.empty()) {
        std::shared_ptr<ASTNode> node = nodes.pop_front();
        if (node->getType() == DECLS) {
            decls = node->getSubtree();
        } else if (node->getType() == STATEMENTS) {
            stmts = node->getSubtree();
        }
    }
    makeCodeDECLS(decls);
    makeCodeSTATEMENTS(stmts);
}

void CodeBuilder::makeCode() {
    std::shared_ptr<ASTNode> node = astCreator.getParentNode();
    makeCodePROG(node->getSubtree());
}