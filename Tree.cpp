//
// Created by alexc on 1/18/2019.
//

#include "Tree.h"

int Tree::_space = 0;
node Tree::_arr[AR_SIZE];

void Tree::InitArr()
{
    for (int i = 0; i < AR_SIZE; i++)
    {
        if(i != AR_SIZE - 1) { //Если не конец строки
            Tree::_arr[i].next = i + 1; //Указываем на следующи элемент
        } else {
            Tree::_arr[i].next = -1; //Указываем на конец списка
        }
    }
    Tree::_space = 0; //Устанавливаем позицию первого элемента списка пустых
}

Tree::Tree()
{
    _tpos = 0;
}

Tree::~Tree()
{
//    for(int i = 0; i < AR_SIZE; i++)
//    {
//        if(Tree::_arr[i].child != nullptr)
//        {
//            if(Tree::_arr[i].child -> next != nullptr)
//            {
//                delete Tree::_arr[i].child -> next;
//            }
//            delete Tree::_arr[i].child;
//        }
//    }
}

Tree& Tree::create(char label)
{
    setRoot(label);
    return *this;
}

Tree& Tree::create(char label, Tree t1)
{
    setRoot(label);
    Tree::_arr[_tpos].child = new child_list(t1._tpos, nullptr);
    t1._tpos = -1;
    return *this;
}

Tree& Tree::create(char label, Tree t1, Tree t2)
{
    setRoot(label);
    child_list * temp;
    temp = new child_list(t2._tpos, nullptr);
    Tree::_arr[_tpos].child = new child_list(t1._tpos, temp);
    t1._tpos = -1;
    t2._tpos = -1;
    return *this;
}

int Tree::leftmost_child(int n)
{
    if(n != _tpos)
    {
        if(searchParent(n, _tpos))
        {
            return -1;
        }
    }
    node temp = Tree::_arr[n];
    int i_temp = -1;
    while(temp.child != nullptr)
    {
        i_temp = temp.child -> position;
        temp = Tree::_arr[temp.child -> position];
    }
    return i_temp;
}

int Tree::right_sibling(int n)
{
    if(n == _tpos)
    {
        return -1;
    } else
    {
        int par = searchParent(n, _tpos);
        if(par == -1)
        {
            return -1;
        }
        if(Tree::_arr[par].child -> next == nullptr)
        {
            return -1;
        }
        return Tree::_arr[par].child -> next -> position;
    }
}

int Tree::parent(int n)
{
    return searchParent(n, _tpos);
}

int Tree::searchParent(int n, int cur)
{
    int check = 0;
    if(Tree::_arr[cur].child == nullptr)
    {
        return -1;
    } else
    {
        if(Tree::_arr[cur].child -> position == n)
        {
            return cur;
        } else
        {
            check = searchParent(n, Tree::_arr[cur].child -> position);
            if(check != -1)
            {
                return check;
            }
        }
    }
    if(Tree::_arr[cur].child -> next == nullptr)
    {
        return -1;
    } else
    {
        if(Tree::_arr[cur].child -> next -> position == n)
        {
            return cur;
        } else
        {
            check = searchParent(n, Tree::_arr[cur].child -> next -> position);
            if(check != -1)
            {
                return check;
            }
        }
    }
    return check;
}

void Tree::makenull()
{
//    node iter = Tree::_arr[_tpos];
//    while()
//    {
//
//    }
}

void Tree::print()
{
//    std::cout << std::setw(5) << "i ";
//    std::cout << std::setw(5) << "data ";
//    std::cout << std::setw(5) << "next ";
//    std::cout << std::setw(5) << "chi " << std::endl;
    for (int i = 0; i < AR_SIZE; ++i)
    {
        std::cout << std::setw(5) << i << " ";
        std::cout << std::setw(5) << Tree::_arr[i].label << " ";
        std::cout << std::setw(5) << Tree::_arr[i].next << " ";
        if(Tree::_arr[i].child != nullptr)
        {
            std::cout << std::setw(5) << "[" << Tree::_arr[i].child -> position << "]";
            if(Tree::_arr[i].child -> next != nullptr)
            {
                std::cout << " -> [" << Tree::_arr[i].child -> next -> position << "]";
            }
        } else
        {
            std::cout << std::setw(5) << "*";
        }
        std::cout << std::endl;
    }
}

void Tree::setRoot(char label)
{
    _tpos = Tree::_space;
    Tree::_space = Tree::_arr[Tree::_space].next;
    Tree::_arr[_tpos].label = label;
}