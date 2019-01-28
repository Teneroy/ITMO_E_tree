//
// Created by alexc on 1/18/2019.
//

#include "Tree.h"
using namespace childlist;
node err;

void traversal(Tree & t, int n)
{
    int lmc = t.leftmost_child(n);
    if(lmc != err.next)
    {
        traversal(t, lmc);
    }
    std::cout << t.label(n);
    int rs = t.right_sibling(lmc);
    if(rs != err.next)
    {
        traversal(t, rs);
    }
}

void traversal(Tree & t)
{
    std::cout << "TRAVERSAL: ";
    int l_child = t.leftmost_child(t.root());
    while(t.parent(l_child) != t.root())
    {
        l_child = t.parent(l_child);
    }
    traversal(t, l_child);
    std::cout << t.label(t.root());
    int r_sibling = t.right_sibling(l_child);
    if(r_sibling != err.next)
        traversal(t, r_sibling);
    std::cout << std::endl;
}

int main()
{
    Tree::InitArr();
    Tree t1;
    Tree t2;
    Tree t3;
    Tree t4;

    t2.create('a');
    t3.create('b');
    t1.create('c', t2, t3);
    t2.create('o');
    t3.create('x', t2, t1);
    t2.create('l');
    t1.create('z');
    t4.create('m', t1, t2);
    t1.create('n', t4, t3);
    t1.print();
    std::cout << std::endl;
    traversal(t1);
    t1.makenull();
    t1.print();

return 0;
}