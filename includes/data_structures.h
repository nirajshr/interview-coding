template <typename T>
class Node {
  public:
    Node (T const& value) : next(0), val(value) {}
    void appendToTail(T const& value) {
      Node<T>* end = new Node<T>(value);

      Node<T>* n = this;
      while (n->next) {
        n = n->next;
      }
      n->next = end;
    }

    Node* next;
    T val;
};

template <typename T>
class Stack {
  public:
    Stack() : top(0) {}
    ~Stack() {
      while(top) {
        Node<T>* temp = top->next;
        delete top;
        top = temp;
      }
    }

    bool empty() {
      return !top;
    }

    T peek() {
      return top->val;
    }

    T pop() {
      T val = top->val;
      Node<T>* next = top->next;
      delete top;
      top = next;
      return val;
    }

    void push(T const& value) {
      Node<T>* temp = top;

      top = new Node<T>(value);
      top->next = temp;
    }

  private:
    Node<T>* top;
};

template <typename T>
class Queue {
  public:
    Queue() : first(0), last(0) {}

    bool empty() {
      return !first;
    }
    void enqueue(T const& value) {
      Node<T>* n = new Node<T>(value);

      if (!first) { 
        first = n;
        last = n;
      }
      else {
        last->next = n;
        last = n;
      }
    }

    T dequeue() {
      Node<T>* temp = first;
      T val = temp->val;

      first = temp->next;
      delete temp;
      return val;
    }

  private:
    Node<T>* first;
    Node<T>* last;
};

template <typename T>
class BinaryTree {
  public:
    BinaryTree (T const& val) : left(0), right(0), parent(0), data(val) {}
  public:
    BinaryTree<T>* left;
    BinaryTree<T>* right;
    BinaryTree<T>* parent;;
    T data;
};

template <typename T>
BinaryTree<T>* searchTree(BinaryTree<T>* tree, T const& val) {
  if (tree) {
    if (tree->data == val) return tree;

    if (val < tree->data) return searchTree(tree->left, val);
    else return searchTree(tree->right, val);
  }

  return 0;
}

template <typename T>
void insert_tree(BinaryTree<T>** tree, T const& val, BinaryTree<T>* parent) {
  if (*tree == 0) { BinaryTree<T>* t = new BinaryTree<T>(val);
    t->parent = parent;
    *tree = t;
  }
  else {
    if ( (*tree)->data < val ) {
      insert_tree( &((*tree)->right), val, *tree);
    }
    else if ( (*tree)->data > val ) {
      insert_tree( &((*tree)->left), val, *tree);
    }
  }
}

template <typename T>
void traverse_tree(BinaryTree<T>* tree, void (*visit)(BinaryTree<T>* tree)) {
  if (tree) {
    traverse_tree<T>(tree->left, visit);
    visit(tree);
    traverse_tree<T>(tree->right, visit);
  }
}

template <typename T>
void traverse_tree_breadth_first_impl(
    Stack<BinaryTree<T>* >* stack_of_tree,
    void (*visit)(BinaryTree<T>* tree)) {

  Stack<BinaryTree<T>* > child_stack;

  while(!stack_of_tree->empty()) {
    BinaryTree<T>* tree = stack_of_tree->pop();
    if (tree) {
      visit(tree);
      child_stack.push(tree->left);
      child_stack.push(tree->right);
    }
  };

  if (!child_stack.empty()) {
    traverse_tree_breadth_first_impl(&child_stack, visit);
  }
}

template <typename T>
void traverse_tree_breadth_first(BinaryTree<T>* tree, void (*visit)(BinaryTree<T>* tree)) {
  Stack<BinaryTree<T>* > stack_of_tree;
  stack_of_tree.push(tree);

  traverse_tree_breadth_first_impl(&stack_of_tree, visit);
}

template <typename T>
BinaryTree<T>* findMin(BinaryTree<T>* tree) {
  if (tree == 0) return 0;
  if (tree->left == 0) {
    return tree;
  }
  else {
    return findMin(tree->left);
  }
}

template <typename T>
BinaryTree<T>* findMax(BinaryTree<T>* tree) {
  if (tree == 0) return 0;
  if (tree->right == 0) {
    return tree;
  }
  else {
    return findMax(tree->right);
  }
}
