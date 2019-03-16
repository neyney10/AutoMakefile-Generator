
#include <iostream>
#include "Tree.hpp"
#include "fake1.hpp"
using std::cout, std::endl, ariel::Tree, ariel::Node;

int main()
{

    Tree* t1 = new Tree();
    Tree t2 = Tree();
    t1->insert(2.3);
    t1->insert(43.11);
    t1->insert(1.22);
    t1->insert(7.2123);
    t1->remove(1.22);
    t1->remove(2.3);
    t1->insert(-3.22);
    t2.insert(5.3);
    t2.insert(2.3);
    t2.insert(1.3);
    t2.insert(8.3);
    try {
        t2.insert(2.3);
    }
    catch (...) {
        cout << "EXCEPTION COUGHT WHEN INSERTING!!\n";
    }
    cout << "&(t1)=" << &t1 << ", &(t2)=" << &t2 << "\n";
    cout << "size(t1)=" << t1->size() << ", size(t2)=" << t2.size() << "\n";
    t1->print();
    t2.print();
t2.print();
    delete t1;
    
}