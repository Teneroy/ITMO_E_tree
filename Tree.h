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
            next = EMPTY;
            child = nullptr;
        };
    };

    class Tree {
    public:
        Tree();
        ~Tree();
        int parent(int n) const;
        char label(int n) const;
        int root() const;
        int leftmost_child(int n) const;
        int right_sibling(int n) const;
        Tree& create(char label);
        Tree& create(char label, Tree & t1);
        Tree& create(char label, Tree & t1, Tree & t2);
        void makenull();
        void print() const;
        static void InitArr();
    private:
        int _tpos; //Позиция корня дерева
        static node _arr[AR_SIZE];
        static int _space;
        void setRoot(char label); //Создание корня дерева
        int searchParent(int n, int cur) const; //Функция поиска родителя
        void deleteTree(int n);  //Функция удаления дерева
    };
}

namespace lcrs {

    enum {AR_SIZE = 15, EMPTY = -1};

    struct node
    {
        int left_child; //Левый сын
        int right_sibling; //Правый брат
        int next; //Дополнительное поле, используется в фейковом объекте
        char label; //Метка
        node()
        {
            left_child = EMPTY;
            right_sibling = EMPTY;
            label = '\0';
            next = -1;
        };
    };

    class Tree {
    public:
        Tree();
        int parent(int n) const;
        char label(int n) const;
        int leftmost_child(int n) const;
        int right_sibling(int n) const;
        Tree& create(char label);
        Tree& create(char label, Tree & t1);
        Tree& create(char label, Tree & t1, Tree & t2);
        void makenull();
        void print() const;
        int root() const;
        static void InitArr();
    private:
        int _tpos;//Позиция корня дерева
        static node _arr[AR_SIZE];
        static int _space;
        void setRoot(char label);//Создание корня дерева
        int searchParent(int n, int cur) const;//Функция поиска родителя
        void deleteTree(int n); //Фунция удаления дерева
    };
}

#endif //ITMO_E_TREE_TREE_H
