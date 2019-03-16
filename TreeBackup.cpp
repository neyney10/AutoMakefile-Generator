#include <iostream>
#include <stdexcept>

// The one and only application object

using namespace std;

class Node
{
  private:
    double value;
    Node *left;
    Node *right;
    Node *parent;

  public:
    Node()
    {
        value = 0;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
    Node(const double val)
    {
        value = val;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
    Node(const double val, Node *const l, Node *const r)
    {
        set_value(val);
        left = l;
        right = r;
    }

    double get_value() { return this->value; }
    Node *get_left() { return left; }
    Node *get_right() { return right; }
    Node *get_parent() { return parent; }

    void set_value(double val) { value = val; }
    void set_left(Node *const l) { left = l; }
    void set_right(Node *const r) { right = r; }
    void set_parent(Node *const p) { parent = p; }
};

class Tree
{
  private:
    Node *_root;
    unsigned int _size;

    void print(Node *n)
    {
        if (n == NULL)
            return;

        print(n->get_left());
        cout << n->get_value() << " ";
        print(n->get_right());
    }

  public:
    int calc_size(Node *tempNode)
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
    int mySize()
    {
        if (_root != NULL)
        {
            Node *t = _root;
            return calc_size(t);
        }
        return 0;
    }
    double right(double i)
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
    double left(double i)
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
    double parent(double i)
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
    double root()
    {
        if (_root != NULL)
            return _root->get_value();
        else
            throw std::invalid_argument("The root is empty");

        return 0;
    }
    unsigned int size()
    {
        return _size;
    }
    Tree() { _root = NULL; }
    void insert(double value)
    {
        Node *n = new Node(value);

        if (_root == NULL)
        {
            _root = n;
        }
        else
        {
            Node *i = _root;
            while (i != NULL)
            {
                if (value == i->get_value())
                    throw std::invalid_argument("The value already exists");
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
                        break;
                    }
                }
            }
        }
        _size++;
    }
    Node *find_predecessor(Node *n)
    {
        if (n == NULL)
            return NULL; //TODO THROW

        if (n->get_left() != NULL)
        {
            n = n->get_left();
            while (n->get_right() != NULL)
                n = n->get_right();

            cout << n->get_value() << "-PREDECESSKR  ";
            return n;
        }
        else
            return NULL;
    }

    Node *find_successor(Node *n)
    {
        if (n == NULL)
            return NULL; //TODO THROW

        if (n->get_right() != NULL)
        {
            n = n->get_right();
            while (n->get_left() != NULL)
                n = n->get_left();

            cout << n->get_value() << "-SUCCESTEST   \n";
            return n;
        }
        else
            return NULL;
    }

    bool contains(double i)
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

    void remove(double val) // TODO
    {
        if (!contains(val))
            throw std::invalid_argument("ERROR : trying to remove Node which isn't exsits");
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
                    if (p != NULL)
                    {
                        if (!orientation)
                            p->set_left(NULL);
                        else
                            p->set_right(NULL);
                    }

                    delete t;
                }
                else if (t->get_left() != NULL && t->get_right() == NULL) // if have only left child
                {
                    Node *pred = find_predecessor(t);
                    Node *pred_p = pred->get_parent();

                    double num = pred->get_value();
                    remove(pred->get_value());
                    t->set_value(num);
                }
                else if (t->get_left() == NULL && t->get_right() != NULL) // if have only right child
                {
                    Node *pred = find_successor(t);
                    Node *pred_p = pred->get_parent();

                    double num = pred->get_value();
                    remove(pred->get_value());
                    t->set_value(num);
                }
                else if (t->get_left() != NULL && t->get_right() != NULL) // if have otwo childrens
                {
                    Node *pred = find_successor(t);
                    Node *pred_p = pred->get_parent();

                    double num = pred->get_value();
                    remove(pred->get_value());
                    t->set_value(num);
                }
            }
        }
    }

    void print()
    {
        if (_root == NULL)
        {
            cout << "The tree is empty.\n";
            return;
        }
        print(_root);
    }
};

int main()
{
    Tree *t = new Tree();
    t->print();
    t->insert(5.0);
    t->insert(7.0);
    t->insert(2.0);
    t->insert(15);
    t->insert(14);
    t->insert(13);
    t->insert(12);
    t->insert(13.5);
    t->insert(1.8);
    t->print();
    cout << "\n";
    //t->remove(9);
    t->remove(2);

    //t->remove(2);
    t->print();

    //	int a;
    //	cin >> a;
    return 0;
}
