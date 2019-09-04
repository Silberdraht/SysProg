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

void CodeBuilder::makeCodeDECLS(Link_List<Token> tokens) {
    if (tokens.empty()) {
        return;
        //return (char *) "";
    }
    Token token = tokens.pop_front();
    Link_List<Token> declaration;
    while (token.tokenType != SignToken && symtable.lookup(token.storage.key).getLexem()[0] != ';') {
        declaration.push_back(token);
        token = tokens.pop_front();
    }
    makeCodeDECL(declaration);
    makeCodeDECLS(tokens);
}


void CodeBuilder::makeCodeDECL(Link_List<Token> tokens) {
    int size = 1;
    char* identifier;
    while (!tokens.empty()) {
        Token token = tokens.pop_front();
        switch (token.tokenType) {
            case IdentifierToken:
                identifier = symtable.lookup(token.storage.key).getLexem();
                break;
            case DigitToken:
                size = (int) token.storage.number;
                break;
            default: break;

        }
    }

    stream << "DS " << identifier << " " << size;
}

void CodeBuilder::makeCodeSTATEMENTS(Link_List<Token> tokens) {
    if (tokens.empty()) {
        return;
        //return (char *) "";
    }
    Token token = tokens.pop_front();
    Link_List<Token> statement;
    while (token.tokenType != SignToken && symtable.lookup(token.storage.key).getLexem()[0] != ';') {
        statement.push_back(token);
        token = tokens.pop_front();
    }
    makeCodeSTATEMENT(statement);
    makeCodeSTATEMENTS(tokens);
}

void CodeBuilder::makeCodeSTATEMENT(Link_List<Token> tokens) {

    Token token = tokens.pop_front();
    if (token.tokenType == IfToken) {
        Link_List<Token> exp = getTokensFromWithinBrackets(tokens, '(', ')');

        Link_List<Token> statement1;
        while (token.tokenType != ElseToken) {
            token = tokens.pop_front();
            statement1.push_back(token);
        }
        statement1.pop_back();

        Link_List<Token> statement2;
        while (!tokens.empty()) {
            statement2.push_back(tokens.pop_front());
        }

        makeCodeEXP(exp);
        int label1 = label_counter;
        label_counter++;
        int label2 = label_counter;
        label_counter++;
        //JIN #LABEL + label1
        stream << "JIN #LABEL" << label1 << " ";
        makeCodeSTATEMENT(statement1);
        stream << "JMP #LABEL" << label2 << " ";
        stream << "#LABEL" << label1 << " NOP ";
        //JMP #LABEL + label2
        //#LABEL + label1 NOP
        makeCodeSTATEMENT(statement2);

        //#LABEL + label2 NOP
    }

    else if (token.tokenType == WhileToken) {
        Link_List<Token> exp = getTokensFromWithinBrackets(tokens, '(', ')');

        Link_List<Token> statement;
        while (token.tokenType != ElseToken) {
            token = tokens.pop_front();
            statement.push_back(token);
        }
        statement.pop_back();

        int label1 = label_counter;
        label_counter++;
        int label2 = label_counter;
        label_counter++;
        //#LABEL1 NOP
        stream << "#LABEL" << label1 << " NOP ";
        makeCodeEXP(exp);
        //JIN #LABEL2
        stream << "JIN #LABEL" << label2 << " ";
        makeCodeSTATEMENT(statement);
        stream << "JMP #LABEL" << label1 << " ";
        stream << "#LABEL" << label2 << " NOP ";
        //JMP #LABEL1
        //#LABEL2 NOP
    }

    else if (token.tokenType == WriteToken) {
        //Token token = tokens.get_front();
        //if (token.tokenType == SignToken && symtable.lookup(token.storage.key).getLexem()[0] == '('){
        tokens.pop_front();
        tokens.pop_back();
        makeCodeEXP(tokens);
        stream << "PRI ";
        //PRI
    }

    else if (token.tokenType == ReadToken) {
        tokens.pop_front();
        tokens.pop_back();
        //REA
        stream << "REA ";
        Token identifierToken = tokens.pop_front();
        char* identifier = symtable.lookup(identifierToken.storage.key).getLexem();
        //LA $identifier
        stream << "LA $" << identifier << " ";
        makeCodeINDEX(tokens);
        stream << "STR ";
        //STR
    }

    else if (token.tokenType == IdentifierToken) {
        char* identifier = symtable.lookup(token.storage.key).getLexem();
        //LA $identifier
        stream << "LA $" << identifier << " ";
        Link_List<Token> index = getTokensFromWithinBrackets(tokens, '[', ']');
        tokens.pop_front(); //:=
        makeCodeINDEX(tokens);
        stream << "STR ";
        //STR
    }

    else if (token.tokenType == SignToken) { //getLexem() == {
        tokens.pop_back();
        makeCodeSTATEMENTS(tokens);
    }

    else {
        //NOP oder STP (incorrect syntax)
    }

}



void CodeBuilder::makeCodeEXP(Link_List<Token> tokens) {
    Link_List<Token> exp2;
    Token token = tokens.pop_front();
    int bracketsOpen = 0;
    int bracketsClose = 0;
    while ((token.tokenType != IdentifierToken && token.tokenType != IntToken) || bracketsOpen != bracketsClose) {
        if (token.tokenType == SignToken) {
            if (symtable.lookup(token.storage.key).getLexem()[0] == '(') {
                bracketsOpen++;
            } else if (symtable.lookup(token.storage.key).getLexem()[0] == ')') {
                bracketsClose++;
            }
        }
        exp2.push_back(token);
        token = tokens.pop_front();
    }
    Token operand = tokens.pop_front();
    char* lexem = symtable.lookup(operand.storage.key).getLexem();
    if (lexem[0] == '>') {
        exp2.push_front(operand);
        makeCodeEXP2(tokens);
        makeCodeOP_EXP(exp2);
    } else if (lexem[0] == '=' && lexem[1] == ':') {
        tokens.push_front(operand);
        makeCodeEXP2(exp2);
        makeCodeOP_EXP(tokens);
        stream << "NOT ";
        //NOT
    }
    else {
        makeCodeEXP2(exp2);
        makeCodeOP_EXP(tokens);
    }

}

void CodeBuilder::makeCodeEXP2(Link_List<Token> tokens) {
    Token token = tokens.pop_front();
    if (token.tokenType == IdentifierToken) {
        char* identifier = symtable.lookup(token.storage.key).getLexem();
        //LA $identifier
        stream << "LA $" << identifier << " ";
        makeCodeINDEX(tokens);
        stream << "LV ";
        //LV
    }
    else if (token.tokenType == IntToken) {
        int integer = (int) token.storage.number;
        stream << "LC " << integer << " ";
        //LC integer
    }
    else if (token.tokenType == SignToken) {
        char c = symtable.lookup(token.storage.key).getLexem()[0];
        if (c == '-') {
            //LC 0
            stream << "LC 0 ";
            makeCodeEXP2(tokens);
            stream << "SUB ";
            //SUB
        }
        else if (c == '!') {
            stream << "NOT ";
            //NOT
        }
        else if (c == '(') {
            tokens.pop_back();
            makeCodeEXP(tokens);
        }
    }

}

void CodeBuilder::makeCodeOP_EXP(Link_List<Token> tokens) {
    Token operand = tokens.pop_front();
    makeCodeEXP(tokens);
    makeCodeOP(operand);
}

void CodeBuilder::makeCodeINDEX(Link_List<Token> tokens) {
    tokens.pop_front();
    tokens.pop_back();
    if (!tokens.empty()) {
        makeCodeEXP(tokens);
        stream << "ADD ";
        //ADD
    } else {
        //return (char *) "";
    }

}


void CodeBuilder::makeCodeOP(Token token) {
    char* result;
    char *sign = symtable.lookup(token.storage.key).getLexem();
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