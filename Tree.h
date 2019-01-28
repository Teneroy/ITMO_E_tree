//
// Created by alexc on 1/18/2019.
//

#ifndef ITMO_E_TREE_TREE_H
#define ITMO_E_TREE_TREE_H

#include <iostream>
#include <iomanip>
#include "string.h"

namespace childlist {

    enum {AR_SIZE = 15, EMPTY = -1}; //Размер массива, пустое ли дерево

    struct child_list //Список детей
    {
        int position; //Позиция на которой данный ребенок
        child_list * next; //Указатель на следующий элемент в списке
        child_list()
        {
            position = 0;
            next = nullptr;
        }
        child_list(int p, child_list * n):position(p)
        {
            next = n;
        }
    };

    struct node
    {
        char label; //Метка
        int next; //Следующий элемент массива пустых
        child_list * child; //Список детей
        node()
        {
            label = '\0';
            next = -1;
            child = nullptr;
        };
        node(char l, int n, child_list * c):label(l),next(n)
        {
            child = c;
        };
    };

    class Tree {
    public:
        Tree();
        ~Tree();
        int parent(int n);
        char label(int n);
        int root();
        int leftmost_child(int n);
        int right_sibling(int n);
        Tree& create(char label);
        Tree& create(char label, Tree t1);
        Tree& create(char label, Tree t1, Tree t2);
        void makenull();
        void print();
        static void InitArr();
    private:
        int _tpos; //Позиция корня дерева
        static node _arr[AR_SIZE];
        static int _space;
        void setRoot(char label); //Создание корня дерева
        int searchParent(int n, int cur);
        void deleteTree(int n);
    };
}

namespace lcrs {

    enum {AR_SIZE = 15, EMPTY = -1};

    struct node
    {
        int left_child; //Левый сын
        int right_sibling; //Правый брат
        int next;
        char label; //Метка
        node()
        {
            left_child = EMPTY;
            right_sibling = EMPTY;
            label = '\0';
            next = -1;
        };
        node(int l, int r, char lb):left_child(l),right_sibling(r),label(lb)
        {};
    };

    class Tree {
    public:
        Tree();
        int parent(int n);
        char label(int n);
        int leftmost_child(int n);
        int right_sibling(int n);
        Tree& create(char label);
        Tree& create(char label, Tree t1);
        Tree& create(char label, Tree t1, Tree t2);
        void makenull();
        void print();
        int root();
        static void InitArr();
    private:
        int _tpos;//Позиция корня дерева
        static node _arr[AR_SIZE];
        static int _space;
        void setRoot(char label);//Создание корня дерева
        int searchParent(int n, int cur);//Функция поиска родителя элемента
        int searchSub(int st, int check, int current, int n);//Дополнительная функция(используется в searchParent)
        void deleteTree(int n);
    };
}

#endif //ITMO_E_TREE_TREE_H
