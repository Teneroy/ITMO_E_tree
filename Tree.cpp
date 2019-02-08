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
    if(_tpos != EMPTY) //Если дерево не пустое
    {
        makenull();
    }
}

childlist::Tree& childlist::Tree::create(char label)
{
    setRoot(label); //Установить корень дерева
    return *this;
}

childlist::Tree& childlist::Tree::create(char label, Tree & t1)
{
    if(t1._tpos != EMPTY) //Если корень дерева не пустой
    {
        setRoot(label); //Установить корень дерева
        Tree::_arr[_tpos].child = new child_list(t1._tpos, nullptr); //Создать список сыновей
        t1._tpos = EMPTY; //Обнулить скопированное дерево
    }
    return *this;
}

childlist::Tree& childlist::Tree::create(char label, Tree & t1, Tree & t2)
{
    setRoot(label);
    if(t1._tpos != EMPTY && t2._tpos != EMPTY) //Если корни первого и второго дерева не пустые
    {
        child_list * temp;
        temp = new child_list(t2._tpos, nullptr);//Создать правое поддерево
        Tree::_arr[_tpos].child = new child_list(t1._tpos, temp);//Создать список сыновей
        t1._tpos = EMPTY;//Обнулить скопированное дерево
        t2._tpos = EMPTY;//Обнулить скопированное дерево
    }
    return *this;
}

char childlist::Tree::label(int n) const
{
    if(n != _tpos) //Если позиция не является корнем дерева
    {
        if(searchParent(n, _tpos) == EMPTY) //Если узла нету в дереве
        {
            return error.label; //Вернуть фейковый элемент
        }
    }
    return Tree::_arr[n].label;
}

int childlist::Tree::leftmost_child(int n) const
{
    if(n != _tpos)//Если позиция не является корнем дерева
    {
        if(searchParent(n, _tpos) == EMPTY)//Если узла нету в дереве
        {
            return error.next; //Вернуть фейковый элемент
        }
    }
    node temp = Tree::_arr[n]; //Создаем итератор
    int i_temp = EMPTY;
    while(temp.child != nullptr) //Спускаемся вниз до самого левого элемента
    {
        i_temp = temp.child -> position; //Записываем позицию узла левого поддерева
        temp = Tree::_arr[temp.child -> position];
    }
    return i_temp; //Возвращаем самый левый узел
}

int childlist::Tree::right_sibling(int n) const
{
    if(n == _tpos) //Если позиция  является корнем дерева
    {
        return error.next; //Вернуть фейковый элемент
    } else
    {
        int par = searchParent(n, _tpos);
        if(par == EMPTY)//Если узла нету в дереве
        {
            return error.next;//Вернуть фейковый элемент
        }
        if(Tree::_arr[par].child -> next == nullptr)
        {
            return error.next; //Вернуть фейковый элемент
        }
        return Tree::_arr[par].child -> next -> position;
    }
}

int childlist::Tree::parent(int n) const
{
    int sp = searchParent(n, _tpos);
    if(sp == EMPTY)//Если узла нету в дереве
    {
        return error.next;//Вернуть фейковый элемент
    }
    return sp;
}

int childlist::Tree::searchParent(int n, int cur) const
{
    int check = 0;
    if(Tree::_arr[cur].child == nullptr) //Если сыновей нету
    {
        return EMPTY; //Вернуть пестой узел
    } else
    {
        if(Tree::_arr[cur].child -> position == n) //Если позиция левого сынаравна поиску
        {
            return cur; //Вернуть позицию родителя
        } else
        {
            check = searchParent(n, Tree::_arr[cur].child -> position); //Искать дальше в левом поддереве
        }
    }
    if(check == -1) //Если слева ничего не нашли
    {
        if(Tree::_arr[cur].child -> next == nullptr) //Если правого сына нету
        {
            return EMPTY; //Вернуть пустой узел
        } else
        {
            if(Tree::_arr[cur].child -> next -> position == n) //Если позиция правого сынаравна поиску
            {
                return cur;//Вернуть позицию родителя
            } else
            {
                check = searchParent(n, Tree::_arr[cur].child -> next -> position);//Искать дальше в правом поддереве
            }
        }
    }
    return check;
}

void childlist::Tree::deleteTree(int n)
{
    if(Tree::_arr[n].child != nullptr) //Если сыновья существуют
    {
        if(Tree::_arr[n].child -> next != nullptr) //Если правый сын существует
        {
            deleteTree(Tree::_arr[n].child -> next -> position); //Ищем в правом поддереве
            delete Tree::_arr[n].child -> next;  //Удалить правый узел
        }
        deleteTree(Tree::_arr[n].child -> position); //Ищем в левом поддереве
        delete Tree::_arr[n].child; //Удаляем левого сына
        Tree::_arr[n].child = nullptr;
    }
    Tree::_arr[n].next = Tree::_space; //Указазываем следующий элемент на первый элемент в списке пустых
    Tree::_space = n; //Новым началом списка пустых, теперь является позиция текущео элемента
}

int childlist::Tree::root() const
{
    return _tpos; //Вернуть корень
}

void childlist::Tree::makenull()
{
    deleteTree(_tpos); //Удаляем дерево
    _tpos = EMPTY; //Зануляем корень дерева
}

void childlist::Tree::print() const
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
    _tpos = Tree::_space; //Корень дерева, теперь имеет значения первого элемента в списке пустых
    Tree::_space = Tree::_arr[Tree::_space].next; //Задаем новый первый элемент списка пустых
    Tree::_arr[_tpos].label = label; //Устанавливаем метку
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

lcrs::Tree& lcrs::Tree::create(char label, Tree & t1)
{
    setRoot(label);
    if(t1._tpos != EMPTY)
    {
        Tree::_arr[_tpos].left_child = t1._tpos;
        t1._tpos = EMPTY;
    }
    return *this;
}

lcrs::Tree& lcrs::Tree::create(char label, Tree & t1, Tree & t2)
{
    setRoot(label);
    if(t1._tpos != EMPTY && t2._tpos != EMPTY)
    {
        Tree::_arr[_tpos].left_child = t1._tpos;
        Tree::_arr[Tree::_arr[_tpos].left_child].right_sibling = t2._tpos;
        t1._tpos = EMPTY;
        t2._tpos = EMPTY;
    }
    return *this;
}

char lcrs::Tree::label(int n) const
{
    if(n != _tpos)//Если позиция не является корнем дерева
    {
        if(searchParent(n, _tpos) == EMPTY) //Если узла нету в дереве
        {
            return error_r.label;//Вернуть фейковый элемент
        }
    }
    return Tree::_arr[n].label;
}

int lcrs::Tree::leftmost_child(int n) const
{
    if(n != _tpos)//Если позиция не является корнем дерева
    {
        if(searchParent(n, _tpos) == EMPTY) //Если узла нету в дереве
        {
            return error_r.next;//Вернуть фейковый элемент
        }
    }
    int iter = Tree::_arr[n].left_child; //Создаем итератор
    while(iter != EMPTY) //Гоним самого левого элемента
    {
        if(Tree::_arr[iter].left_child) //Если левый сын существует следующего узла
            return iter; //Вернуть итератор
        iter = Tree::_arr[iter].left_child;
    }
    return iter;
}

int lcrs::Tree::right_sibling(int n) const
{
    if(n == _tpos)//Если позиция является корнем дерева
    {
        return error_r.next;//Вернуть фейковый элемент
    }
    int par = searchParent(n, _tpos);
    if (par == EMPTY)
    {
        return error_r.next;//Вернуть фейковый элемент
    }
    return Tree::_arr[n].right_sibling;
}

int lcrs::Tree::parent(int n) const
{
    int par = searchParent(n, _tpos);
    if(par == EMPTY) //Если узла нету в дереве
    {
        return error_r.next;//Вернуть фейковый элемент
    }
    return par;
}

void lcrs::Tree::print() const
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
    deleteTree(_tpos); //Уаляем дерево
    _tpos = -1;//Зануляем корень дерева
}

int lcrs::Tree::searchParent(int n, int cur) const
{
    int check = 0;
    if(Tree::_arr[cur].left_child == EMPTY)//Если сыновей нету
    {
        return EMPTY;//Вернуть пустой узел
    } else
    {
        if(Tree::_arr[cur].left_child == n)//Если позиция левого сынаравна поиску
        {
            return cur;//Вернуть позицию родителя
        } else
        {
            check = searchParent(n, Tree::_arr[cur].left_child);//Искать дальше в левом поддереве
        }
    }
    if(check == EMPTY)//Если слева ничего не нашли
    {
        if(Tree::_arr[Tree::_arr[cur].left_child].right_sibling == EMPTY)//Если правого сына нету
        {
            return EMPTY;//Вернуть пустой узел
        } else
        {
            if(Tree::_arr[Tree::_arr[cur].left_child].right_sibling == n)//Если позиция правого сынаравна поиску
            {
                return cur;//Вернуть позицию родителя
            } else
            {
                check = searchParent(n, Tree::_arr[Tree::_arr[cur].left_child].right_sibling);//Искать дальше в правом поддереве
            }
        }
    }
    return check;
}

int lcrs::Tree::root() const
{
    return _tpos; //Вернуть корень дерева
}

void lcrs::Tree::setRoot(char label)
{
    _tpos = Tree::_space;//Корень дерева, теперь имеет значения первого элемента в списке пустых
    Tree::_space = Tree::_arr[_tpos].right_sibling;//Задаем новый первый элемент списка пустых
    Tree::_arr[_tpos].left_child = EMPTY;
    Tree::_arr[_tpos].right_sibling = EMPTY;
    Tree::_arr[_tpos].label = label;
}

void lcrs::Tree::deleteTree(int n)
{
    int lc = Tree::_arr[n].left_child;
    if(lc != EMPTY)//Если сыновья существуют
    {
        int rs = Tree::_arr[lc].right_sibling;
        if(rs != EMPTY)//Если правый сын существует
        {
            deleteTree(rs);//Ищем в правом поддереве
        }
        deleteTree(lc);//Ищем в левом поддереве
    }
    Tree::_arr[n].right_sibling = Tree::_space;//Указазываем следующий элемент на первый элемент в списке пустых
    Tree::_space = n;//Новым началом списка пустых, теперь является позиция текущео элемента
}
