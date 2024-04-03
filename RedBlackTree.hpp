#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

namespace JC {
  class RedBlackTree {
  public:
    RedBlackTree();
    void insert();
    void remove();

  private:
    void maintainInvariant();
  };
}

#endif

