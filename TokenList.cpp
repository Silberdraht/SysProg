////
//// Created by noahp on 23/04/2019.
////
//
//#include "TokenList.h"
//
//
//TokenList::TokenList() {
//    head = nullptr;
//
//}
//
//TokenList::~TokenList() {
//
//    Symbol *next = head;
//    while (next) {
//
//        Symbol *deleteSymbol = next;
//        next = next->next;
////        delete deleteSymbol;
//    }
//
//}
//
//void TokenList::addToken(Token token) {
//    if (head == nullptr) {
//        head = new Symbol();
//        head->token = token;
//    }
//    else {
//        Symbol *s = head;
//        while (s->next != nullptr) {
//            s = s->next;
//        }
//        auto *toAdd = new Symbol();
//        toAdd->token = token;
//        s->next = toAdd;
//    }
//    countSymbol++;
//}
//
//
//Token TokenList::popToken() {
//    if (countSymbol > 0) {
//
//        countSymbol--;
//
//        Symbol *s = head;
//        Token t = s->token;
//
//        head = head->next;
//        //delete s;
//
//        return t;
//    }
//}
//
//Token TokenList::getToken(int index) {
//
//    Token token;
//    if (countSymbol > index) {
//        Symbol *s = head;
//        for (int i=0; i < index; i++) {
//            s = head->next;
//        }
//
//        token = s->token;
//    }
//
//    return token;
//}
//
//bool TokenList::isEmpty() {
//
//    return countSymbol <= 0;
//}
//
//int TokenList::listLength() {
//
//    return countSymbol;
//}
