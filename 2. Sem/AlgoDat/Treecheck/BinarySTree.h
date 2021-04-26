#pragma once
#include <iostream>

using namespace std;

class BinarySTree {

public:
	int key;
	BinarySTree* left, * right;

	BinarySTree();
	BinarySTree(int value);

	BinarySTree* insert(BinarySTree* root, int value);

	void inOrder(BinarySTree*);
};
