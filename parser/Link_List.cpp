//
// Created by Nil on 17.08.2019.
//

#include "Link_List.h"

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
    T *s_first = first;
    first = first->predessesor;
    first->successor = nullptr;
    delete (s_first);
    return first->content;
}

template<typename T>
T Link_List<T>::pop_back() {
    T *s_last = last;
    last  = last->predessesor;
    last->predessesor = nullptr;
    delete (s_last);
    return last->content;
}

template<typename T>
void Link_List<T>::push_front(T add_obj) {
    auto elm = new Element<T>();
    elm->content = add_obj;
    if(size() == 0){
        first = &elm;
        last = &elm;
    } else {
        first->successor = elm;
        elm->predessesor = first;
        first = elm;
        elm.successor = nullptr;
    }
}

template<typename T>
void Link_List<T>::push_back(T add_obj) {
    auto elm = new Element<T>();
    elm->content = add_obj;
    if (size() > 0){
        first = &elm;
        last = &elm;
        i_size++;
    } else {
        last->predessesor = &elm;
        elm->successor = last;
        last = &elm;
        last->predessesor = nullptr;
        i_size++;
    }
}

template<typename T>
T Link_List<T>::get_front() {
    return first->content;
}

template<typename T>
T Link_List<T>::get_back() {
    return last->content;
}
