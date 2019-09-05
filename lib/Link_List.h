//
// Created by Nil on 17.08.2019.
//

#ifndef SYSPROG_LINK_LIST_H
#define SYSPROG_LINK_LIST_H

#include <memory>

template <typename T>
class Element {
public:
    T content;
    std::shared_ptr<Element<T>> predecessor = nullptr;
    std::shared_ptr<Element<T>> successor = nullptr;
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
    T front();
    T back();
    T end();
    T begin();
    T at(int position);


private:
    std::shared_ptr<Element<T>> first = nullptr;
    std::shared_ptr<Element<T>> last = nullptr;
    int i_size = 0;
};

template<typename T>
bool Link_List<T>::empty() {
    return (i_size == 0);
}

template<typename T>
int Link_List<T>::size() {
    return i_size;
}

template<typename T>
T Link_List<T>::pop_front() {
    T s_first = first.operator*().content;
    if(i_size == 1){
        last = nullptr;
        first = nullptr;
    } else{
        first = first->predecessor;
        first->successor = nullptr;
    }
    i_size--;
    return s_first;
}

template<typename T>
T Link_List<T>::pop_back() {
    T s_last = last.operator*().content;
    if(i_size == 1) {
        last = nullptr;
        first = nullptr;
    }
    else {
        last  = last->successor;
        last->predecessor = nullptr;
    }
    i_size--;
    return s_last;
}

template<typename T>
void Link_List<T>::push_front(T add_obj) {
    std::shared_ptr<Element<T>> elm = std::make_shared<Element<T>>();
    elm.operator*().content = add_obj;
    if(size() == 0){
        first = elm;
        last = elm;
    } else {
        first->successor = elm;
        elm->predecessor = first;
        first = elm;
        elm->successor = nullptr;
    }
    i_size++;
}

template<typename T>
void Link_List<T>::push_back(T add_obj) {
    auto elm = std::make_shared<Element<T>>();
    elm.operator*().content = add_obj;
    if (size() == 0){
        first = elm;
        last = elm;
    } else {
        last->predecessor = elm;
        elm->successor = last;
        last = elm;
        last->predecessor = nullptr;
    }
    i_size++;
}

template<typename T>
T Link_List<T>::front() {
    return first->content;
}

template<typename T>
T Link_List<T>::back() {
    return last->content;
}

#endif //SYSPROG_LINK_LIST_H
