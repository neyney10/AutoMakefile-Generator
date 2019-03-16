#include <iostream>

namespace ariel
{

class Node
{
private:
  double value;
  Node *left;
  Node *right;
  Node *parent;

public:
  Node() : Node(0) {}
  Node(const double val) : Node(val, NULL, NULL) {}
  Node(const double val, Node *const l, Node *const r) : value(val), left(l), right(r), parent(NULL) {}

  ~Node()
  {
    if (left != NULL)
      delete left;

    if (right != NULL)
      delete right;
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

// TREE
class Tree
{
private:
  Node *_root;
  unsigned int _size;

  Node *find_predecessor(Node *n);
  Node *find_successor(Node *n);
  void print(Node *n);

public:
  // Constructor
  Tree() : _root(NULL), _size(0) {}
  ~Tree()
  {
    if (_root != NULL)
      delete _root;
  }

  int calc_size(Node *tempNode); //TODO REMOVE (?)
  int mySize();
  double right(double i);
  double left(double i);
  double parent(double i);
  double root();
  unsigned int size();
  void insert(double value);
  bool contains(double i);
  void remove(double val);
  void print();
};
} // namespace ariel