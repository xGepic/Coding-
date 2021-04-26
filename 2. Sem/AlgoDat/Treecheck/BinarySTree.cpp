#include "BinarySTree.h"

BinarySTree::BinarySTree() {

	key = 0;
	left = NULL;
	right = NULL;
}

BinarySTree::BinarySTree(int value) {

	key = value;
	left = right = NULL;
}

BinarySTree* BinarySTree::insert(BinarySTree* root, int value) {

	if (!root) {

		return new BinarySTree(value);
	}

	if (value > root->key) {

		root->right = insert(root->right, value);
	}
	else if (value < root->key) {

		root->left = insert(root->left, value);
	}
	// duplicates not allowed

	return root;
}

void BinarySTree::inOrder(BinarySTree* root) {

	if (!root) {

		return;
	}

	inOrder(root->left);
	cout << root->key << endl;
	inOrder(root->right);
}