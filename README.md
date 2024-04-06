# Data-Structures

## Problem Statement
Implement a Red Black Tree data structure. That is
- a binary tree
- each node is either red or black
- Supports the following operations
    - insert
    - delete
- tree can be re-arranged and re-painted when modified
- the length of the longest root-leaf path should be no more than twice that of the shortest
- maintains the following invariants
    1. A red node cannot have a red child
    2. Every root-leaf path contains the same number of black nodes

## Corollaries
### If a node has a red child, then both children are red.
Proof: Suppose not. That is, node N has one red child and a black child.
Then, the path to a leaf through the subtree rooted at the red child
has one less black node than the path to a leaf through the subtree rooted
at N's black child.

## Algorithms

### Maintaining Invariants
if N root
    DONE
if P is black
    DONE
if P is root:
    assert P red
    P.color = black
    DONE
if U is black
    if N is inner grandchild
        make N outer grandchild
    rotate G down
    change G to red, P to black
    DONE
if U is red
    change P & U to black, G to red
    G = N
    continue

#### So I don't forget
'''
export CXX=/opt/homebrew/bin/g++-13
'''

