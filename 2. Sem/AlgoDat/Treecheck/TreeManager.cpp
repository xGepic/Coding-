#include "TreeManager.h"
#include "BinarySTree.h"

TreeManager::TreeManager() {

	root = NULL;
	avl = true;
}

TreeManager::~TreeManager() {

	DeleteTree(root);
}

// destuctor
void TreeManager::DeleteTree(BinarySTree* tree) {

	if (tree != NULL) {

		DeleteTree(tree->left);
		DeleteTree(tree->right);
		delete tree;
	}
}

// returns root
BinarySTree* TreeManager::getRoot() {

	return root;
}

// returns the maximum depth of the tree
// basically searches for the longest path and returns its length
int TreeManager::depthSearch(BinarySTree* node) {

	if (node == NULL) {

		return 0;
	}
	else {

		return max(depthSearch(node->left), depthSearch(node->right)) + 1;
	}
}

// returns balance factor if node not null
int TreeManager::balanceFactor(BinarySTree* node) {

	if (node == NULL) {

		return 0;
	}
	else {

		return depthSearch(node->right) - depthSearch(node->left);
	}
}

// prints balance factor for all nodes in tree in inverse reverse pre-order
// right, left, node
// bal(k) = depth(right subtree) - depth(left subtree).
// and adds avl violation warning when violation occurs
void TreeManager::avlCheck(BinarySTree* node) {

	int balance;

	if (node != NULL) {

		avlCheck(node->right);
		avlCheck(node->left);

		balance = balanceFactor(node);
		cout << "bal(" << node->key << ") = " << balance;

		if ((balance < -1) || (balance > 1)) {

			cout << " (AVL violation!)";
			avl = false;
		}
		cout << endl;
	}

	if (node == root) {

		cout << "AVL: ";

		if (avl) {

			cout << "yes" << endl;
		}
		else {

			cout << "no" << endl;
		}
	}
}

// calls avlCheck and returns the smallest key, biggest key and average key
// (average = sumkeys / numberofkeys)
void TreeManager::statisticsCheck() {

	avlCheck(root);
	double sumKeys = statisticsSumKeys(root);
	double countKeys = statisticsCountKeys(root);
	cout << "min: " << statisticsMinKey(root) << ", ";
	cout << "max: " << statisticsMaxKey(root) << ", ";
	cout << "avg: " << sumKeys / countKeys << endl;
}

// goes though the tree and returns the amount of keys in the tree
// count = (current_node) 1 + left_count + right_count
// if node == 0 return 0
int TreeManager::statisticsCountKeys(BinarySTree* node) {

	if (node == NULL) {

		return 0;
	}
	else {

		return 1 + statisticsCountKeys(node->left) + statisticsCountKeys(node->right);
	}
}

// goes though the tree and returns the sum of all keys
// sum = current->key + sum(left) + sum(right)
// if node == 0 return 0
int TreeManager::statisticsSumKeys(BinarySTree* node) {

	if (node == NULL) {

		return 0;
	}
	else {

		//cout << node->key << "sum " << endl;
		return node->key + statisticsSumKeys(node->left) + statisticsSumKeys(node->right);
	}
}

// finds left-most node in the tree and returns the key
// since it is a binary search tree, the right-most element is always the smallest
int TreeManager::statisticsMinKey(BinarySTree* node) {

	if (node != NULL) {

		if (node->left == NULL) {

			return node->key;
		}
		else {

			return statisticsMinKey(node->left);
		}
	}
	else {

		return 0;
	}
}

// finds right-most node in the tree and returns the key
// since it is a binary search tree, the right-most element is always the biggest
int TreeManager::statisticsMaxKey(BinarySTree* node) {

	if (node != NULL) {

		if (node->right == NULL) {

			return node->key;
		}
		else {

			return statisticsMaxKey(node->right);
		}
	}
	else {

		return 0;
	}
}

// searches for key in tree
// returns true if key exists in tree
bool TreeManager::pathExists(BinarySTree* node, int findKey) {

	if (node == NULL) {

		return false;
	}
	else {

		if (node->key == findKey) {

			return true;
		}
		else if (node->key > findKey) {

			return pathExists(node->left, findKey);
		}
		// node->key < findKey
		else {

			return pathExists(node->right, findKey);
		}
	}
}

// only get called for existing key
// tracks path from root/node to findKey in the tree
// and prints the path
void TreeManager::findPath(BinarySTree* node, int findKey) {

	if (node != NULL) {

		if (node == root) {

			cout << findKey << " found ";
		}
		else {

			cout << ", ";
		}
		cout << node->key;

		if (node->key == findKey) {

			cout << endl;
		}
		else if (node->key > findKey) {

			findPath(node->left, findKey);
		}
		// node->key < findKey
		else {

			findPath(node->right, findKey);
		}
	}
}

// if subtree is not empty
// either searches for the one key if it is a one-element-tree
// or checks whether the subtree is part of root and returns found or not found
void TreeManager::searchSubtree(BinarySTree* subtree) {

	if (subtree == NULL) {

		cout << "Subtree is empty." << endl;
	}
	else {

		if (subtree->left == NULL && subtree->right == NULL) {

			searchOneKey(subtree->key);
		}
		else {

			if (searchMultiple(root, subtree)) {

				cout << "Subtree found" << endl;
			}
			else {

				cout << "Subtree not found" << endl;
			}
		}
	}

}

// searches fot subtree->key in tree
// when found, calls the searchMultiple() for subtree->left and subtree->right as well
// with corresponding tree-left/tree->right
// so that the nodes from tree branch the same way as the nodes from subtree
// all the descandants from a node in subtree have the same descendant in tree as well
// (if node exists in tree)
bool TreeManager::searchMultiple(BinarySTree* tree, BinarySTree* subtree) {

	if (subtree == NULL) {

		return true;
	}
	if (tree == NULL) {

		return false;
	}

	if (tree->key == subtree->key) {

		return searchMultiple(tree->left, subtree->left) && searchMultiple(tree->right, subtree->right);
	}
	else if (tree->key > subtree->key) {

		return searchMultiple(tree->left, subtree);
	}
	// tree->key < subtree->key
	else {

		return searchMultiple(tree->right, subtree);
	}
}


// if a path to a node with key==findKey exists
// the path is printed, otherwise not
void TreeManager::searchOneKey(int findKey) {

	if (pathExists(root, findKey)) {

		findPath(root, findKey);
	}
	else {

		cout << findKey << " not found!" << endl;
	}
}

//
bool TreeManager::readFile(string fileName) {

	fileName += ".txt";

	ifstream textread(fileName);
	vector<string> data;
	vector<int> intNumbers;
	string line;

	while (getline(textread, line)) {

		data.push_back(line);
	}

	textread.close();

	data.erase(unique(data.begin(), data.end()), data.end());

	for (auto& s : data) {

		stringstream parser(s);
		int x = 0;
		parser >> x;
		intNumbers.push_back(x);
	}

	int n = intNumbers.size();

	for (int i = 0; i < n; i++) {

		root = root->insert(root, intNumbers[i]);
	}

	return 0;
}