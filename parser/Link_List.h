//
// Created by Nil on 17.08.2019.
//

#ifndef SYSPROG_LINK_LIST_H
#define SYSPROG_LINK_LIST_H

template <typename E>
class Element {
public:
    E *content;
    E *predessesor;
    E *successor;
};

template <typename T>
class Link_List {
public:
    bool empty();
    int size();
    T pop_front();
    void push_front(T add_obj);
    T pop_back();
    void push_back(T add_obj);
    T get_front();
    T get_back();

private:
    Element<T> *first = nullptr;
    Element<T> *last = nullptr;
    int i_size = 0;
};

#endif //SYSPROG_LINK_LIST_H
