//
// Created by noahp on 21/08/2019.
//

#include <fstream>
#include "../lib/Link_List.h"
#include "CodeBuilder.h"

CodeBuilder::CodeBuilder(ASTCreator astCreator, Symtable symTable) : astCreator(astCreator), symtable(symTable) {
}
CodeBuilder::~CodeBuilder() = default;

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
    bool identifierFound = false;
    while(!nodes.empty()) {
        std::shared_ptr<ASTNode> node = nodes.pop_front();
        if (node->getType() == IDENTIFIER) {
            identifier = symtable.lookup(node->getKey()).getLexem();
            identifierFound = true;
        } else if (node->getType() == ARRAY) {
            array = node->getSubtree();
        }
    }

    if (!identifierFound) {
        std::cout << "Identifier expected in declaration";
        return;
    }
    stream.open(file_out, std::fstream::app);
    stream << "DS $" << identifier << " "; // no spaceOrLineBreak
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
    stream << size << spaceOrLineBreak;
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
        stream << "JIN #LABEL" << label1 << spaceOrLineBreak;
        stream.close();
        makeCodeSTATEMENT(statement1);
        stream.open(file_out, std::fstream::app);
        stream << "JMP #LABEL" << label2 << spaceOrLineBreak;
        stream << "#LABEL" << label1 << " NOP" << spaceOrLineBreak;
        stream.close();
        makeCodeSTATEMENT(statement2);
        stream.open(file_out, std::fstream::app);
        stream << "#LABEL" << label2 << " NOP" << spaceOrLineBreak;
        stream.close();
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
        stream << "#LABEL" << label1 << " NOP" << spaceOrLineBreak;
        stream.close();
        makeCodeEXP(exp);
        stream.open(file_out, std::fstream::app);
        stream << "JIN #LABEL" << label2 << spaceOrLineBreak;
        stream.close();
        makeCodeSTATEMENT(statement);
        stream.open(file_out, std::fstream::app);
        stream << "JMP #LABEL" << label1 << spaceOrLineBreak;
        stream << "#LABEL" << label2 << " NOP" << spaceOrLineBreak;
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
        stream << "PRI" << spaceOrLineBreak;
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
            stream << "REA" << spaceOrLineBreak;
            stream << "LA $" << identifier << spaceOrLineBreak;
            stream.close();
            makeCodeINDEX(index);
            stream.open(file_out, std::fstream::app);
            stream << "STR" << spaceOrLineBreak;
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
        stream << "LA $" << identifier << spaceOrLineBreak;
        stream.close();
        makeCodeINDEX(index);
        stream.open(file_out, std::fstream::app);
        stream << "STR" << spaceOrLineBreak;
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


bool CodeBuilder::makeCodeEXP(Link_List<std::shared_ptr<ASTNode>> nodes) {
    bool hasExp2 = false; bool hasOpExp = false;
    std::shared_ptr<ASTNode> exp2;
    std::shared_ptr<ASTNode> op_exp;
    while (!nodes.empty()) {
        std::shared_ptr<ASTNode> node = nodes.pop_front();
        if (node->getType() == EXP2) {
            hasExp2 = true;
            exp2 = node;
        } else if (node->getType() == OP_EXP) {
            hasOpExp = true;
            op_exp = node;
        }
    }

    if (hasOpExp && hasExp2) {
        Link_List<std::shared_ptr<ASTNode>> opExpSubtree = op_exp->getSubtree();
        Link_List<std::shared_ptr<ASTNode>> opSubTree;
        if (opExpSubtree.size() > 0) {
            opSubTree = op_exp->getSubtree().front()->getSubtree();
            if (opSubTree.size() > 0) {
                NodeType opType = opSubTree.front()->getType();
                if (opType == GREATERSIGN) {
                    std::shared_ptr<ASTNode> opOfOp_exp = op_exp->getSubtree().front();
                    std::shared_ptr<ASTNode> expOfOp_exp = op_exp->getSubtree().back();
                    makeCodeEXP(expOfOp_exp->getSubtree());
                    std::shared_ptr<ASTNode> newOP_EXP = std::make_shared<ASTNode>(nullptr, OP_EXP);
                    std::shared_ptr<ASTNode> newEXP = std::make_shared<ASTNode>(newOP_EXP, EXP);
                    newOP_EXP->addChild(opOfOp_exp);
                    newOP_EXP->addChild(newEXP); //->getSubtree().push_back(newExp);
                    newEXP->addChild(exp2);
                    //newExp->parent = op_exp;
                    makeCodeOP_EXP(op_exp->getSubtree());
                } else {
                    makeCodeEXP2(exp2->getSubtree());
                    makeCodeOP_EXP(op_exp->getSubtree());
                    if (opType == EQUPEQUSIGN) {
                        stream.open(file_out, std::fstream::app);
                        stream << "NOT" << spaceOrLineBreak;
                        stream.close();
                    }
                }
                return true;
            }
        }
    }
    if (hasExp2) { // and above code did not reach return
        return makeCodeEXP2(exp2->getSubtree());
    } else {
        return false;
    }
}


bool CodeBuilder::makeCodeEXP2(Link_List<std::shared_ptr<ASTNode>> nodes) {
    if(nodes.empty()) {
        return false;
    }
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
        stream << "LA $" << identifier << spaceOrLineBreak;
        stream.close();
        makeCodeINDEX(index);
        stream.open(file_out, std::fstream::app);
        stream << "LV" << spaceOrLineBreak;
        stream.close();
    }
    else if (node->getType() == INTEGER) {
        int integer = (int) node->getDigit();
        stream.open(file_out, std::fstream::app);
        stream << "LC " << integer << spaceOrLineBreak;
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
        stream << "LC 0" << spaceOrLineBreak;
        stream.close();
        makeCodeEXP2(exp2);
        stream.open(file_out, std::fstream::app);
        stream << "SUB" << spaceOrLineBreak;
        stream.close();

    }
    else if (node->getType() == EXCLSIGN) {
        stream.open(file_out, std::fstream::app);
        stream << "NOT" << spaceOrLineBreak;
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
    return true;
}

void CodeBuilder::makeCodeOP_EXP(Link_List<std::shared_ptr<ASTNode>> nodes) {
    Link_List<std::shared_ptr<ASTNode>> op;
    Link_List<std::shared_ptr<ASTNode>> exp;
    while (!nodes.empty()) {
        std::shared_ptr<ASTNode> node = nodes.pop_front();
        if (node->getType() == OP) {
            op = node->getSubtree();
        } else if (node->getType() == EXP) {
            exp = node->getSubtree();
        } else {
            op.push_front(node); //directly contained operand

        }
    }
    makeCodeEXP(exp);
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
    bool hasIndex = makeCodeEXP(exp);
    if (hasIndex) {
        stream.open(file_out, std::fstream::app);
        stream << "ADD" << spaceOrLineBreak;
        stream.close();
    }

}


void CodeBuilder::makeCodeOP(const std::shared_ptr<ASTNode>& node) {
    //char* result;
    NodeType type = node->getType();
//    char *sign = symtable.lookup(node->getKey()).getLexem();
//    char c = sign[0];
    stream.open(file_out, std::fstream::app);
    if (type == PLUSSIGN) {
        stream << "ADD" << spaceOrLineBreak;
    } else if (type == MINUSSIGN) {
        stream << "SUB" << spaceOrLineBreak;
    } else if (type == STARSIGN) {
        stream << "MUL" << spaceOrLineBreak;
    } else if (type == DOUBLESIGN) {
        stream << "DIV" << spaceOrLineBreak;
    } else if (type == EQUALSSIGN || type == EQUPEQUSIGN) {
        stream << "EQU" << spaceOrLineBreak;
    } else if (type == LESSSIGN) {
        stream << "LES" << spaceOrLineBreak;
    } else if (type == ANDSIGN) {
        stream << "AND" << spaceOrLineBreak;
    } else {
        stream << "NOP" << spaceOrLineBreak; //should never be reached by valid code
    }
    stream.close();
}

void CodeBuilder::makeCodePROG(Link_List<std::shared_ptr<ASTNode>> nodes) {
    while (!nodes.empty()) {
        std::shared_ptr<ASTNode> node = nodes.pop_front();
        if (node->getType() == DECLS) {
            makeCodeDECLS(node->getSubtree());
        } else if (node->getType() == STATEMENTS) {
            makeCodeSTATEMENTS(node->getSubtree());
        }
    }
    stream.open(file_out, std::fstream::app);
    stream << "STP" << spaceOrLineBreak;
    stream.close();
}

void CodeBuilder::makeCode() {
    stream.open(file_out, std::ofstream::out | std::ofstream::trunc);
    stream.close();
    std::shared_ptr<ASTNode> node = astCreator.getParentNode();
    makeCodePROG(node->getSubtree());
}