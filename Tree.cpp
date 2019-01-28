//
// Created by alexc on 1/18/2019.
//

#include "Tree.h"

int childlist::Tree::_space = 0;
childlist::node childlist::Tree::_arr[AR_SIZE];
childlist::node error;

void childlist::Tree::InitArr()
{
    for (int i = 0; i < AR_SIZE; i++)
    {
        if(i != AR_SIZE - 1) { //Если не конец строки
            Tree::_arr[i].next = i + 1; //Указываем на следующи элемент
        }
    }
}

childlist::Tree::Tree()
{
    _tpos = EMPTY;
}

childlist::Tree::~Tree()
{
    if(_tpos != EMPTY) {
        makenull();
    }
}

childlist::Tree& childlist::Tree::create(char label)
{
    setRoot(label);
    return *this;
}

childlist::Tree& childlist::Tree::create(char label, Tree t1)
{
    setRoot(label);
    Tree::_arr[_tpos].child = new child_list(t1._tpos, nullptr);
    t1._tpos = EMPTY;
    return *this;
}

childlist::Tree& childlist::Tree::create(char label, Tree t1, Tree t2)
{
    setRoot(label);
    child_list * temp;
    temp = new child_list(t2._tpos, nullptr);
    Tree::_arr[_tpos].child = new child_list(t1._tpos, temp);
    t1._tpos = EMPTY;
    t2._tpos = EMPTY;
    return *this;
}

char childlist::Tree::label(int n)
{
    if(n != _tpos)
    {
        if(!searchParent(n, _tpos))
        {
            return error.label; //return error
        }
    }
    return Tree::_arr[n].label;
}

int childlist::Tree::leftmost_child(int n)
{
    if(n != _tpos)
    {
        if(searchParent(n, _tpos) == EMPTY)
        {
            return error.next; //return error
        }
    }
    node temp = Tree::_arr[n];
    int i_temp = EMPTY;
    while(temp.child != nullptr)
    {
        i_temp = temp.child -> position;
        temp = Tree::_arr[temp.child -> position];
    }
    return i_temp;
}

int childlist::Tree::right_sibling(int n)
{
    if(n == _tpos)
    {
        return error.next; //return error
    } else
    {
        int par = searchParent(n, _tpos);
        if(par == EMPTY)
        {
            return error.next; //return error
        }
        if(Tree::_arr[par].child -> next == nullptr)
        {
            return error.next; //return error
        }
        return Tree::_arr[par].child -> next -> position;
    }
}

int childlist::Tree::parent(int n)
{
    int sp = searchParent(n, _tpos);
    if(sp == EMPTY)
    {
        return error.next;
    }
    return sp;
}

int childlist::Tree::searchParent(int n, int cur)
{
    int check = 0;
    if(Tree::_arr[cur].child == nullptr)
    {
        return EMPTY;
    } else
    {
        if(Tree::_arr[cur].child -> position == n)
        {
            return cur;
        } else
        {
            check = searchParent(n, Tree::_arr[cur].child -> position);
        }
    }
    if(check == -1)
    {
        if(Tree::_arr[cur].child -> next == nullptr)
        {
            return EMPTY;
        } else
        {
            if(Tree::_arr[cur].child -> next -> position == n)
            {
                return cur;
            } else
            {
                check = searchParent(n, Tree::_arr[cur].child -> next -> position);
            }
        }
    }
    return check;
}

void childlist::Tree::deleteTree(int n)
{
    if(Tree::_arr[n].child != nullptr)
    {
        if(Tree::_arr[n].child -> next != nullptr)
        {
            deleteTree(Tree::_arr[n].child -> next -> position);
            delete Tree::_arr[n].child -> next;
        }
        deleteTree(Tree::_arr[n].child -> position);
        delete Tree::_arr[n].child;
        Tree::_arr[n].child = nullptr;
    }
    Tree::_arr[n].next = Tree::_space;
    Tree::_space = n;
}

int childlist::Tree::root()
{
    return _tpos;
}

void childlist::Tree::makenull()
{
    deleteTree(_tpos);
    _tpos = EMPTY;
}

void childlist::Tree::print()
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

void childlist::Tree::setRoot(char label)
{
    _tpos = Tree::_space;
    Tree::_space = Tree::_arr[Tree::_space].next;
    Tree::_arr[_tpos].label = label;
}

/*_____________________________LEFT CHILD RIGHT SIBLING________________________________*/

int lcrs::Tree::_space = 0;
lcrs::node lcrs::Tree::_arr[AR_SIZE];
lcrs::node error_r;

void lcrs::Tree::InitArr()
{
    for (int i = 0; i < AR_SIZE; i++)
    {
        if(i != AR_SIZE - 1) { //Если не конец строки
            Tree::_arr[i].right_sibling = i + 1; //Указываем на следующи элемент
        }
    }
}

lcrs::Tree::Tree()
{
    _tpos = EMPTY;
}

lcrs::Tree& lcrs::Tree::create(char label)
{
    setRoot(label);
    return *this;
}

lcrs::Tree& lcrs::Tree::create(char label, Tree t1)
{
    setRoot(label);
    Tree::_arr[_tpos].left_child = t1._tpos;
    t1._tpos = -1;
    return *this;
}

lcrs::Tree& lcrs::Tree::create(char label, Tree t1, Tree t2)
{
    setRoot(label);
    Tree::_arr[_tpos].left_child = t1._tpos;
    Tree::_arr[Tree::_arr[_tpos].left_child].right_sibling = t2._tpos;
    t1._tpos = EMPTY;
    t2._tpos = EMPTY;
    return *this;
}

char lcrs::Tree::label(int n)
{
    if(n != _tpos)
    {
        if(searchParent(n, _tpos) == EMPTY)
        {
            return error_r.label;//return error
        }
    }
    return Tree::_arr[n].label;
}

int lcrs::Tree::leftmost_child(int n)
{
    if(n != _tpos)
    {
        if(searchParent(n, _tpos) == EMPTY)
        {
            return error_r.next;//return error
        }
    }
    int iter = Tree::_arr[n].left_child;
    while(iter != EMPTY)
    {
        if(Tree::_arr[iter].left_child)
            return iter;
        iter = Tree::_arr[iter].left_child;
    }
    return iter;
}

int lcrs::Tree::right_sibling(int n)
{
    if(n == _tpos)
    {
        return error_r.next;//return error
    }
    int par = searchParent(n, _tpos);
    if (par == EMPTY)
    {
        return error_r.next;//return error
    }
    return Tree::_arr[n].right_sibling;
}

int lcrs::Tree::parent(int n)
{
    int par = searchParent(n, _tpos);
    if(par == EMPTY)
    {
        return error_r.next;
    }
    return par;
}

void lcrs::Tree::print()
{
    for (int i = 0; i < AR_SIZE; ++i)
    {
        std::cout << std::setw(5) << i << " |";
        std::cout << std::setw(5) << Tree::_arr[i].left_child << " ";
        std::cout << std::setw(5) << Tree::_arr[i].label << " ";
        std::cout << std::setw(5) << Tree::_arr[i].right_sibling << " ";
        std::cout << std::endl;
    }
}

void lcrs::Tree::makenull()
{
    deleteTree(_tpos);
    _tpos = -1;
}

int lcrs::Tree::searchParent(int n, int cur)
{
    int check = 0;
    check = searchSub(Tree::_arr[cur].left_child, check, cur, n);
    if (check == -1 && Tree::_arr[cur].left_child != -1)
    {
        check = searchSub(Tree::_arr[Tree::_arr[cur].left_child].right_sibling, check, cur, n);
    }
    return check;
}

int lcrs::Tree::searchSub(int st, int check, int current, int n)
{
    if(st == EMPTY)
    {
        return -1;
    } else
    {
        if(st == n)
        {
            return current;
        } else
        {
            check = searchParent(n, st);
        }
    }
    return check;
}

int lcrs::Tree::root()
{
    return _tpos;
}

void lcrs::Tree::setRoot(char label)
{
    _tpos = Tree::_space;
    Tree::_space = Tree::_arr[_tpos].right_sibling;
    Tree::_arr[_tpos].left_child = EMPTY;
    Tree::_arr[_tpos].right_sibling = EMPTY;
    Tree::_arr[_tpos].label = label;
}

void lcrs::Tree::deleteTree(int n)
{
    int lc = Tree::_arr[n].left_child;
    if(lc != EMPTY)
    {
        int rs = Tree::_arr[lc].right_sibling;
        if(rs != EMPTY)
        {
            deleteTree(rs);
        }
        deleteTree(lc);
    }
    Tree::_arr[n].right_sibling = Tree::_space;
    Tree::_space = n;
}
