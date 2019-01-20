//
// Created by alexc on 1/18/2019.
//

#ifndef ITMO_E_TREE_TREE_H
#define ITMO_E_TREE_TREE_H

#include <iostream>
#include <iomanip>
#include "string.h"

struct child_list
{
    int position;
    child_list * next;
    child_list()
    {
        position = 0;
        next = nullptr;
    }
    child_list(int p, child_list * n):position(p),next(n)
    {}
};

struct node
{
    char label;
    int next;
    child_list * child;
    node()
    {
        label = '\0';
        next = 0;
        child = nullptr;
    };
    node(char l, int n, child_list * c):label(l),next(n),child(c)
    {};
};

enum {AR_SIZE = 15};

class Tree {
public:
    Tree();
    ~Tree();
    int parent(int n);
    char label(int n){};
    int leftmost_child(int n);
    int right_sibling(int n);
    Tree& create(char label);
    Tree& create(char label, Tree t1);
    Tree& create(char label, Tree t1, Tree t2);
    void makenull();
    void print();
    static void InitArr();
private:
    int _tpos;
    static node _arr[AR_SIZE];
    static int _space;
    void setRoot(char label);
    int searchParent(int n, int cur);
};

#endif //ITMO_E_TREE_TREE_H
