#include <iostream>
#include <stdexcept>
#include "Tree.hpp"


int ariel::Tree::calc_size(Node *tempNode)
{
    if (tempNode == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + calc_size(tempNode->get_left()) + calc_size(tempNode->get_right());
    }
}
int ariel::Tree::mySize()
{
    if (_root != NULL)
    {
        Node *t = _root;
        return calc_size(t);
    }
    return 0;
}
double ariel::Tree::right(double i)
{
    if (_root != NULL)
    {
        if (!contains(i))
        {
            throw std::invalid_argument("i value isnt found and thus doesnt have right child");
        }
        else
        { //i exsists , Lets find him!!!
            Node *t = _root;
            while (t->get_value() != i)
            {
                if (t->get_value() == i)
                    break;
                else if (t->get_value() < i)
                    t = t->get_right();
                else
                    t = t->get_left();
            }
            if (t->get_right() == NULL)
                throw std::invalid_argument("i was found but doesnt have a right child");
            else
                return t->get_right()->get_value(); //not sure if the syntax is right
        }
    }
    else
    {
        throw std::invalid_argument("The root is empty");
    }
}
double ariel::Tree::left(double i)
{
    if (_root != NULL)
    {
        if (!contains(i))
        {
            throw std::invalid_argument("i value isnt found and thus doesnt have left child");
        }
        else
        { //i exsists , Lets find him!!!
            Node *t = _root;
            while (t->get_value() != i)
            {
                if (t->get_value() == i)
                    break;
                else if (t->get_value() < i)
                    t = t->get_right();
                else
                    t = t->get_left();
            }
            if (t->get_left() == NULL)
                throw std::invalid_argument("i was found but doesnt have a left child");
            else
                return t->get_left()->get_value(); //not sure if the syntax is right
        }
    }
    else
    {
        throw std::invalid_argument("The root is empty");
    }
}
double ariel::Tree::parent(double i)
{
    if (_root != NULL)
    {
        if (_root->get_value() == i)
        {
            //throw exception since i is the root
            //thus does not have a father
            throw std::invalid_argument("i is the root and thus doesnt have a father");
        }
        else if (!contains(i))
        {
            throw std::invalid_argument("i wasnt found");
        }
        else
        {
            Node *t = _root;
            while (t->get_value() != i)
            {
                if (t->get_value() == i)
                    break;
                else if (t->get_value() < i)
                    t = t->get_right();
                else
                    t = t->get_left();
            }
            //not sure if this can be done double use of "get"
            return t->get_parent()->get_value();
        }
    }
    else
    {
        throw std::invalid_argument("The root is empty");
    }
}
double ariel::Tree::root()
{
    if (_root != NULL)
        return _root->get_value();
    else
        throw std::invalid_argument("The root is empty");

    return 0;
}
unsigned int ariel::Tree::size()
{
    return _size;
}

void ariel::Tree::insert(double value)
{
    
    if (_root == NULL)
    {
        _root = new Node(value);
        _size++;
        return; // exit
    }

    if(contains(value))
    {
        throw std::invalid_argument("The value is already exists in the tree (value: "+std::to_string(value)+")");
    } else {
        Node *n = new Node(value);
        Node *i = _root;

        while (i != NULL)
        {
            if (value < i->get_value())
            {
                if (i->get_left() != NULL)
                {
                    i = i->get_left();
                }
                else
                {
                    n->set_parent(i);
                    i->set_left(n);
                    _size++;
                    break;
                }
            }
            else
            {
                if (i->get_right() != NULL)
                {
                    i = i->get_right();
                }
                else
                {
                    n->set_parent(i);
                    i->set_right(n);
                    _size++;
                    break;
                }
            }
        }
    }
}
ariel::Node* ariel::Tree::find_predecessor(Node *n)
{
    if (n == NULL)
        return NULL;

    if (n->get_left() != NULL)
    {
        n = n->get_left();
        while (n->get_right() != NULL)
            n = n->get_right();

        return n;
    }
    else
        return NULL;
}

ariel::Node* ariel::Tree::find_successor(Node *n)
{
    if (n == NULL)
        return NULL;

    if (n->get_right() != NULL)
    {
        n = n->get_right();
        while (n->get_left() != NULL)
            n = n->get_left();

        return n;
    }
    else
        return NULL;
}

bool ariel::Tree::contains(double i)
{
    Node *t = _root;
    while (t != NULL)
    {
        if (t->get_value() == i)
            return true;
        else if (t->get_value() < i)
            t = t->get_right();
        else
            t = t->get_left();
    }
    return false;
}

void ariel::Tree::remove(double val)
{
    if (!contains(val))
        throw std::invalid_argument("ERROR : trying to remove Node which doesn't exist");

    //if root is null - tree is empty then exit
    if (_root == NULL)
        return;

    // find the node in the tree
    Node *t = _root;          // temp
    bool orientation = false; // false = left, true = right;
    while (t != NULL)
    {
        if (val < t->get_value())
        {
            orientation = false;
            t = t->get_left();
        }
        else if (val > t->get_value())
        {
            orientation = true;
            t = t->get_right();
        }
        else if (val == t->get_value())
        {

            Node *p = t->get_parent(); // parent
            // if a leaf
            if (t->get_left() == NULL && t->get_right() == NULL)
            {
                if (p != NULL) // the only node without a parent is a root node.
                {
                    if (!orientation)
                        p->set_left(NULL);
                    else
                        p->set_right(NULL);

                    delete t;

                } else {

                    delete _root;
                    _root = NULL;

                }

                this->_size--;
                return; // exit
            }
            else if (t->get_left() != NULL && t->get_right() == NULL) // if have only left child
            {
                Node *pred = find_predecessor(t);
                Node *pred_p = pred->get_parent();

                double num = pred->get_value();
                remove(pred->get_value());
                t->set_value(num);

                return; // exit
            }
            else if (t->get_left() == NULL && t->get_right() != NULL) // if have only right child
            {
                Node *succ = find_successor(t);
                Node *succ_p = succ->get_parent();

                double num = succ->get_value();
                remove(succ->get_value());
                t->set_value(num);

                return; // exit
            }
            else if (t->get_left() != NULL && t->get_right() != NULL) // if have two childrens
            {
                Node *succ = find_successor(t);
                Node *succ_p = succ->get_parent();

                double num = succ->get_value();
                remove(succ->get_value());
                t->set_value(num);

                return; // exit
            }
        }
    }
}

void ariel::Tree::print(Node *n)
{
        if (n == NULL)
            return;

        print(n->get_left());
        std::cout << n->get_value() << " ";
        print(n->get_right());
    }

void ariel::Tree::print()
{
    if (_root == NULL)
    {
        std::cout << "The tree is empty.\n";
        return;
    }
    print(_root);
    std::cout << "\n";
}


