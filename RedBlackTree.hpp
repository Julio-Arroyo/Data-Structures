#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iostream>
#include <iterator>
#include <cassert>
#include <memory>

#define RED false
#define BLACK true

namespace JC {
  class RedBlackTree {
  public:
    class Node : public std::enable_shared_from_this<Node> {
    public:
      Node(int val) : data{val} {}
      Node(int val, std::shared_ptr<Node> parent_) : data{val} {
        parent = parent_;
      }

      std::shared_ptr<Node> getPtr() {
        return shared_from_this();
      }

      void addChild(int val) {
        if (val < data) {
          assert(left == nullptr);
          left = std::make_shared<Node>(val, getPtr());
        } else if (val > data) {
          assert(right == nullptr);
          right = std::make_shared<Node>(val, getPtr());
        } else {
          assert(false);
        }
      }

      int getData() const {
        return data;
      }

      std::shared_ptr<Node> getLeft() const {
        return left;
      }

      std::shared_ptr<Node> getRight() const {
        return right;
      }

      std::shared_ptr<Node> getParent() const {
        return parent;
      }

      bool getColor() const {
        return color;
      }
      
      void setColor(const bool new_color) {
        color = new_color;
      }

      void setLeft(std::shared_ptr<Node> new_left) {
        left = new_left;
      }

      void setRight(std::shared_ptr<Node> new_right) {
        right = new_right;
      }

      void setParent(std::shared_ptr<Node> new_parent) {
        parent = new_parent;
      }

      bool operator<(const Node& other) const {
        return data < other.data;
      }

      bool operator>(const Node& other) const {
        return data > other.data;
      }

      void rotateLeft() {
        std::shared_ptr<Node> other = right;
        assert(other != nullptr);

        other->setParent(parent);
        if (parent != nullptr) {
          if (*other < *parent) {
            parent->setLeft(other);
          } else if (*other > *parent) {
            parent->setRight(other);
          } else {
            assert(false);
          }
        }
        right = other->getLeft();

        if (other->getLeft() != nullptr) {
          other->getLeft()->setParent(getPtr());
        }
        other->setLeft(getPtr());

        parent = other;
      }

      void rotateRight() {
        std::shared_ptr<Node> other = left;
        assert(other != nullptr);

        other->setParent(parent);
        if (parent != nullptr) {
          if (*other < *parent) {
            parent->setLeft(other);
          } else if (*other > *parent) {
            parent->setRight(other);
          } else {
            assert(false);
          }
        }
        left = other->getRight();

        if (other->getRight() != nullptr) {
          other->getRight()->setParent(getPtr());
        }
        other->setRight(getPtr());

        parent = other;
      }

    private:
      int data;
      bool color{RED};
      std::shared_ptr<Node> parent{nullptr};
      std::shared_ptr<Node> left{nullptr};
      std::shared_ptr<Node> right{nullptr};
    };

    class iterator {
    public:
      using value_type = int;
      using difference_type = int;

      explicit iterator() {
        currNode = nullptr;
      }

      explicit iterator(std::shared_ptr<Node> start) {
        currNode = start;
      }

      int operator*() const {
        return currNode->getData();
      }

      // Prefix increment
      iterator& operator++() {
        searchNext();
        return *this;
      }

      // Postfix increment
      iterator operator++(int /* dummy parameter used by compiler to distinguis from prefix */) {
        iterator ret_val = *this;
        searchNext();
        return ret_val;
      }

      bool isEnd() const {
        return currNode == nullptr;
      }

      bool operator==(const iterator& other) const {
        if (currNode == nullptr && other.isEnd()) {
          return true;
        } else if (currNode == nullptr || other.isEnd()) {
          return false;
        } else {
          return currNode->getData() == *other;
        }
      }

      bool operator!=(const iterator& other) const {
        return !(*this == other);
      }

    private:
      void searchNext() {
        int start_key = currNode->getData();

        // Case 1: starting node has no right child
        if (currNode->getRight() == nullptr) {
          // follow parents until you find key > start_key
          while (true) {
            currNode = currNode->getParent();
            if (currNode == nullptr || currNode->getData() > start_key) {
              break;
            }
          }
        }

        // Case 2: starting node has right child
        else {
          // go right once, then as many left's as possible
          currNode = currNode->getRight();
          while (currNode->getLeft() != nullptr) {
            currNode = currNode->getLeft();
          }
          assert(currNode != nullptr);
        }
      }
      std::shared_ptr<Node> currNode{nullptr};
    };
    static_assert(std::input_iterator<iterator>);

    RedBlackTree();

    void insert(int val);
    void remove();
    void visualize() const;
    iterator begin();
    iterator end();

  private:
    void visualize(std::shared_ptr<Node> node, size_t depth) const;
    void maintainInvariants(std::shared_ptr<Node> node);

    std::shared_ptr<Node> root{nullptr};
  };

  RedBlackTree::RedBlackTree() {}

  void RedBlackTree::insert(int val) {
    if (root == nullptr) {
      root = std::make_shared<Node>(val);
      return;
    }

    std::shared_ptr<Node> node = root;
    while (true) {
      if (val < node->getData()) {
        if (node->getLeft() == nullptr) {
          node->addChild(val);
          RedBlackTree::maintainInvariants(node->getLeft());
          break;
        } else {
          node = node->getLeft();
        }
      } else if (val > node->getData()) {
        if (node->getRight() == nullptr) {
          node->addChild(val);
          RedBlackTree::maintainInvariants(node->getRight());
          break;
        } else {
          node = node->getRight();
        }
      } else {
        assert(false);
      }
    }
  }

  void RedBlackTree::visualize(std::shared_ptr<Node> node, size_t depth) const {
    if (node == nullptr) {
      return;
    }

    RedBlackTree::visualize(node->getRight(), depth + 1);
    
    for (size_t i = 0; i < depth; i++) {
      std::cout << "   ";
    }

    if (node->getColor() == RED) {
      std::cout << "\033[1;31m";
    }
    std::cout << node->getData();
    if (node->getColor() == RED) {
      std::cout << "\033[0m";
    }
    std::cout << std::endl;

    RedBlackTree::visualize(node->getLeft(), depth + 1);
  }

  void RedBlackTree::visualize() const {
    RedBlackTree::visualize(root, 0);
  }

  void RedBlackTree::maintainInvariants(std::shared_ptr<Node> n) {
    while (true) {
      assert(n != nullptr);
      assert(n->getColor() == RED);

      // Set p, g, u
      std::shared_ptr<Node> p = n->getParent();
      if (p == nullptr) {
        // n is root, so done
        break;
      }
      std::shared_ptr<Node> g = n->getParent()->getParent();
      std::shared_ptr<Node> u{nullptr};
      if (g != nullptr) {
        if (*p < *g) {
          u = g->getRight();
        } else if (*p > *g) {
          u = g->getLeft();
        } else {
          assert(false);
        }
      }

      if (p->getColor() == BLACK) {
        // no violation
        break;
      }
      else if (g == nullptr) {
        // p is root
        assert(p->getColor() == RED);
        root->setColor(BLACK);
        break;
      }
      else if (u == nullptr || u->getColor() == BLACK) {
        // if n is inner grandchild, make outer
        if (*p < *g) {
          if (*p < *n) {
            p->rotateLeft();

            // re-label
            std::shared_ptr<Node> tmp = p;
            p = n;
            n = tmp;
          }
          if (g == root) {
            root = g->getLeft();
          }
          g->rotateRight();
        } else if (*g < *p) {
          if (*n < *p) {
            p->rotateRight();
            std::shared_ptr<Node> tmp = p;
            p = n;
            n = tmp;
          }
          if (g == root) {
            root = g->getRight();
          }
          g->rotateLeft();
        } else {
          assert(false);
        }
        p->setColor(BLACK);
        g->setColor(RED);
        break;
      }
      else if (u->getColor() == RED) {
        p->setColor(BLACK);
        u->setColor(BLACK);
        g->setColor(RED);
        n = g;
        continue;
      }
      else {
        assert(false);
      }
    }
  }

  RedBlackTree::iterator RedBlackTree::begin() {
    std::shared_ptr<Node> start_node = root;
    while (start_node->getLeft() != nullptr) {
      start_node = start_node->getLeft();
    }
    return RedBlackTree::iterator(start_node);
  }

  RedBlackTree::iterator RedBlackTree::end() {
    return RedBlackTree::iterator();
  }
}

#endif

