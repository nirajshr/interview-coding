//Verify if a given Binary Tree is a Binary Search Tree
//Need to look at all the granchildren with respect to Top level node
#include "data_structures.h"

#include <iostream>

using namespace std;

bool verifyIfBSTImpl(BinaryTree<int>* tree, int low, int high) {
  if (tree) {
    if ( !(tree->data <= high && tree->data >= low) ) return false;

    bool left_result = verifyIfBSTImpl(tree->left, low, tree->data);
    bool right_result = verifyIfBSTImpl(tree->right, tree->data, high);

    return left_result && right_result;
  }

  return true;
}

bool verifyIfBST(BinaryTree<int>* tree) {
  if (tree) {
    return verifyIfBSTImpl(tree, -999, +999);
  }
  return true;
}

void printTreeNode(BinaryTree<int>* tree) {
  std::cout << tree->data << " ";
}

int main() {
  BinaryTree<int>* tree = new BinaryTree<int>(3);
  tree->left = new BinaryTree<int>(2);
  tree->right = new BinaryTree<int>(5);
  tree->left->left = new BinaryTree<int>(1);
  tree->left->right = new BinaryTree<int>(4);

  traverse_tree(tree, printTreeNode);
  bool result = verifyIfBST(tree);
  cout << endl << "Is it a Binary Tree ? " << (result ? "Y" : "N") << endl;
  return 0;
}
