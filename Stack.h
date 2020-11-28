//
// Created by aaron on 9/20/2020.
//
#ifndef PALINDROME_STACK_H
#define PALINDROME_STACK_H
#endif //PALINDROME_STACK_H
#pragma once
#include <string>
using namespace std;


class Stack { //constructor
    int numChar;//number of elements in struct
private:

    struct Node {
        char item;
        Node* tail;
    };
Node* stackPt;

public:
    Stack();
    void Push(const char item);
    char Pop();
    bool emptyStack() const;
};
