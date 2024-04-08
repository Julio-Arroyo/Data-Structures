#include "RedBlackTree.hpp"

int main() {
  JC::RedBlackTree tree;
  // tree.insert(8);
  // tree.insert(4);
  // tree.insert(22);
  // tree.visualize();
  // tree.insert(21);
  // tree.visualize();
  // tree.insert(23);
  // tree.visualize();
  // tree.insert(20);
  // tree.visualize();

  // std::cout << "tree2" << std::endl;
  // JC::RedBlackTree tree2;
  // std::cout << "insert 4" << std::endl;
  // tree2.insert(4);
  // tree2.visualize();
  // std::cout << std::endl;

  // std::cout << "insert 8 " << std::endl;
  // tree2.insert(8);
  // tree2.visualize();
  // std::cout << std::endl;

  // std::cout << "insert 20" << std::endl;
  // tree2.insert(20);
  // tree2.visualize();
  // std::cout << std::endl;

  // std::cout << "insert 21" << std::endl;
  // tree2.insert(21);
  // tree2.visualize();
  // std::cout << std::endl;

  // std::cout << "insert 22" << std::endl;
  // tree2.insert(22);
  // tree2.visualize();
  // std::cout << std::endl;

  // std::cout << "insert 23" << std::endl;
  // tree2.insert(23);
  // tree2.visualize();
  // std::cout << "Done" << std::endl;
  //
  std::cout << "tree2" << std::endl;
  JC::RedBlackTree tree2;
  std::cout << "insert 4" << std::endl;
  tree2.insert(4);
  tree2.visualize();
  std::cout << std::endl;

  std::cout << "insert 23" << std::endl;
  tree2.insert(23);
  tree2.visualize();

  std::cout << "insert 8 " << std::endl;
  tree2.insert(8);
  tree2.visualize();
  std::cout << std::endl;

  std::cout << "insert 22" << std::endl;
  tree2.insert(22);
  tree2.visualize();
  std::cout << std::endl;

  std::cout << "insert 21" << std::endl;
  tree2.insert(21);
  tree2.visualize();
  std::cout << std::endl;

  std::cout << "insert 20" << std::endl;
  tree2.insert(20);
  tree2.visualize();
  std::cout << std::endl;

  std::cout << "Begin iterator test " << std::endl;
  JC::RedBlackTree::iterator it = tree2.begin();
  while (!it.isEnd()) {
    std::cout << *it << std::endl;
    it++;
  }

  std::cout << "Done" << std::endl;
  return 0;
}
