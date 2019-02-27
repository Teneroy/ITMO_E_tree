//
// Created by alexc on 1/18/2019.
//

#include "Tree.h"
using namespace childlist;

void traversal(Tree & t, int n)
{
    int lmc = t.leftmost_child(n);
    if(lmc >= 0)
    {
        traversal(t, lmc);
    }
    std::cout << t.label(n);
    int rs = t.right_sibling(lmc);
    if(rs >= 0)
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
    if(r_sibling >= 0)
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
//    std::cout << "LEFTMOSTCHILD  0  --->>> " << t1.leftmost_child(0) << std::endl;
//    std::cout << "LEFTMOSTCHILD  1  --->>> " << t1.leftmost_child(1) << std::endl;
//    std::cout << "LEFTMOSTCHILD  2  --->>> " << t1.leftmost_child(2) << std::endl;
//    std::cout << "LEFTMOSTCHILD  3  --->>> " << t1.leftmost_child(3) << std::endl;
//    std::cout << "LEFTMOSTCHILD  4  --->>> " << t1.leftmost_child(4) << std::endl;
//    std::cout << "LEFTMOSTCHILD  5  --->>> " << t1.leftmost_child(5) << std::endl;
//    std::cout << "LEFTMOSTCHILD  6  --->>> " << t1.leftmost_child(6) << std::endl;
//    std::cout << "LEFTMOSTCHILD  7  --->>> " << t1.leftmost_child(7) << std::endl;
//    std::cout << "LEFTMOSTCHILD  8  --->>> " << t1.leftmost_child(8) << std::endl;
//    std::cout << "LEFTMOSTCHILD  9  --->>> " << t1.leftmost_child(9) << std::endl;

    traversal(t1);
    t1.makenull();
    t1.print();

return 0;
}