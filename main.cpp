//
// Created by alexc on 1/18/2019.
//

#include "Tree.h"

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
    //std::cout << t1.leftmost_child(2) << std::endl;
    t2.create('o');
    t3.create('x', t2, t1);
    t2.create('l');
    t1.create('z');
    t4.create('m', t1, t2);
    t1.create('n', t4, t3);
    t1.print();
    std::cout << "PARENT(10): " << t1.parent(10) << std::endl;

return 0;
}