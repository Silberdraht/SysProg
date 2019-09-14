//
// Created by noahp on 13/09/2019.
//

#ifndef SYSPROG_STACK_H
#define SYSPROG_STACK_H

#include <memory>

template <typename T>
class Content {
public:
    T content;
    std::shared_ptr<Content<T>> successor = nullptr;

};

template <typename T>
class Stack {
public:
    bool empty();
    int size();
    T pop_front();
    void push_front(T add_obj);
    T front();
    T at(int position);
    std::shared_ptr<Content<T>> getFirst();

private:
    std::shared_ptr<Content<T>> first = nullptr;
    int i_size = 0;
};

template<typename T>
bool Stack<T>::empty() {
    return (i_size == 0);
}

template<typename T>
int Stack<T>::size() {
    return i_size;
}

template<typename T>
T Stack<T>::pop_front() {
    T s_first = first.operator*().content;
    if(i_size == 1){
        first = nullptr;
    } else {
        first = first->successor;
    }
    i_size--;
    return s_first;
}

template<typename T>
void Stack<T>::push_front(T add_obj) {
    std::shared_ptr<Content<T>> elm = std::make_shared<Content<T>>();
    elm.operator*().content = add_obj;
    if(size() == 0){
        first = elm;
    } else {
        elm->successor = first;
        first = elm;
    }
    i_size++;
}

template<typename T>
T Stack<T>::front() {
    return first->content;
}

template<typename T>
T Stack<T>::at(int position) {
    Content<T>* element = first.get();
    for(int i = 0; i < position-1; i++){
        element = (element->successor).get();
    }
    return element->content;
}


#endif //SYSPROG_STACK_H