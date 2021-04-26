#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "BinarySTree.h"

using namespace std;

class TreeManager {

private:
    bool avl;
    BinarySTree* root;

public:
    TreeManager();
    ~TreeManager();
    void DeleteTree(BinarySTree* tree);

    //reads tree from file
    bool readFile(string fileName);
    // returns root
    BinarySTree* getRoot();

    // returns depth/height of the tree
    int depthSearch(BinarySTree* node);
    // return balance factor of tree
    int balanceFactor(BinarySTree* node);
    // prints balance factors and avl true/false in inverse postorder (right -> left -> node)
    void avlCheck(BinarySTree* node);

    // calls avlCheck(root) and prints min/max/average key values
    void statisticsCheck();
    // returns number of nodes
    int statisticsCountKeys(BinarySTree* node);
    //returns the sum of all keys
    int statisticsSumKeys(BinarySTree* node);
    //returns lefs-most (smallest) key value
    int statisticsMinKey(BinarySTree* node);
    // returns right-most (biggest)  key value
    int statisticsMaxKey(BinarySTree* node);

    // calls either searchOneKey or searchMultiple depending on number of nodes in subtree
    void searchSubtree(BinarySTree* subtree);

    // if the key exists in root-tree prints the path, otherwise not
    void searchOneKey(int findKey);
    // returns whether or not the key can be found in the tree
    bool pathExists(BinarySTree* node, int findKey);
    // follows path from node to node-with-key and prints values
    void findPath(BinarySTree* node, int findKey);

    // returns whether or not all of the nodes form subtree exist in tree
    // only true if the nodes branch out the same way as well
    bool searchMultiple(BinarySTree* tree, BinarySTree* subtree);
};
