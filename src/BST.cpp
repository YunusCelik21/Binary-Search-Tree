/**
* Title: Binary Search Tree 
* Author : Yunus Celik
* ID: 22203347
* Section : 1
* Homework : 1
* Description : This file contians the BST class, and deletePointedNode friend function implementation
*/

#include "BST.h"
#include <algorithm>
#define println(x) std::cout << x << std::endl
#define print(x) std::cout << x

static bool noComma = true; // if true, first element to be printed will not have a comma at its left

BST::BST(int keys[], int size) { 
		this->left = nullptr;
		this->right = nullptr;
		this->value = INT16_MAX; // tree is empty

	if (size != 0) {
		this->value = keys[0];

		for (int i = 1; i < size; ++i) {
			this->insertKeyNoMessage(keys[i]);
		}
	}

	println("BST with size " << size << " is created.");
}

BST::BST(int value) : value(value), left(nullptr), right(nullptr) {}

BST::~BST() {
	if (this->left) {
		delete this->left;
	}

	if (this->right) {
		delete this->right;
	}
}

void BST::insertKey(int key) {
	if (insertKeyNoMessage(key)) {
		println("Key " << key << " is added.");
	}
	else {
		println("Key " << key << " is not added. It exists!");
	}
}

bool BST::insertKeyNoMessage(int key) { // required to insert recursively, otherwise will print twice
	if (isEmpty()) {
		this->value = key;
		return true;
	}

	if (key < this->value) { 
		if (this->left) {
			return this->left->insertKeyNoMessage(key);
		}

		this->left = new BST(key);
		return true;	
	}
	else if (key > this->value) {
		if (this->right) {
			return this->right->insertKeyNoMessage(key);
		}

		this->right = new BST(key);
		return true;
	}

	return false;	
}

void BST::deleteKey(int key) {
	if (deleteKeyNoMessage(key)) {
		println("Key " << key << " is deleted.");
	}
	else {
		println("Key " << key << " is not deleted. It does not exist!");
	}
}

bool BST::deleteKeyNoMessage(int key) { // required to call delete recursively, otherwise will print twice
	if ((key < this->value && !this->left) || (key > this->value && !this->right)) {
		return false;
	}

	if (key < this->value) {
		if (this->left->value == key) {
			deletePointedNode(this->left);
			return true;
		}

		return this->left->deleteKeyNoMessage(key);
	}
	else if (key > this->value) {
		if (this->right->value == key) {
			deletePointedNode(this->right);
			return true;
		}

		return this->right->deleteKeyNoMessage(key);
	}
	else {
		deleteRoot();
		return true;
	}

	return false;
}

void deletePointedNode(BST*& node) { // deletes the pointed node and updates the original pointer to that node
	if (!node->right && !node->left) {
		delete node;
		node = nullptr;
	}
	else if (node->right && !node->left) {
		BST* del = node;
		node = del->right;
		del->right = nullptr;
		delete del;
	}
	else if (!node->right && node->left) {
		BST* del = node;
		node = del->left;
		del->left = nullptr;
		delete del;
	}
	else {
		node->deleteRoot();
	}
}

void BST::deleteRoot() { // deleting the root is a special case
	if (!this->left && !this->right) {
		this->value = INT16_MAX; // tree is empty now
	}
	else if (!this->left) {
		BST* del = this->right;

		// root now is the right node
		this->right = del->right;
		this->left = del->left;
		this->value = del->value;

		// delete the right node
		del->right = nullptr;
		del->left = nullptr;
		delete del;
	}
	else if (!this->right) {
		BST* del = this->left;

		// root now is the left node
		this->right = del->right;
		this->left = del->left;
		this->value = del->value;

		// delete the left node
		del->right = nullptr;
		del->left = nullptr;
		delete del;
	}
	else {
		int successor = inorderSuccessor();
		this->deleteKeyNoMessage(successor);
		this->value = successor;
	}
}


int BST::inorderSuccessor() { 
	if (!this->right) {
		return this->value;
	}
	
	return this->right->smallest();
}

int BST::smallest() { // returns the smallest key in the tree
	if (!this->left) {
		return this->value;
	}

	return this->left->smallest();
}

void BST::displayInorder() {
	print("Inorder display is: ");

	if (!isEmpty()) {
		printInorder();
		noComma = true; // next method's message should start with no comma
	}
	print("\n");
}

void BST::printInorder() {
	if (this->left) {
		this->left->printInorder();
	}

	if (noComma) {
		print(this->value);
		noComma = false;
	}
	else {
		print(", " << this->value);
	}

	if (this->right) {
		this->right->printInorder();
	}
}

void BST::findFullBTLevel() { 
	int level = 0;
	while (isLevelFull(level)) {
		++level;
	}

	println("Full binary tree level is: " << level - 1);
}

bool BST::isLevelFull(int level) {
	if (level == 0) {
		return true;
	}

	if (level == 1) {
		return !isEmpty();
	}

	if (level == 2) {
		return this->left && this->right;
	}

	return (this->left && this->right) && this->left->isLevelFull(level - 1) && this->right->isLevelFull(level - 1);
}

void BST::lowestCommonAncestor(int A, int B) {
	int res = lowestCommon(A, B);
	print("Lowest common ancestor of " << A << " and " << B << " is: ");

	if (res > 0) {
		print(res);
	}
	print("\n");
}

int BST::lowestCommon(int A, int B) { // required in pathFromAtoB, so implemented in another method
	if (depth(A) < 0 || depth(B) < 0) {
		return -1; // no lowest common
	}
	int min = A < B ? A : B;
	int max = A > B ? A : B;

	BST* commonAncestor = this;
	while (!(commonAncestor->value <= max && commonAncestor->value >= min)) { // while common ancestor is not in between
		if (commonAncestor->value > max) {
			commonAncestor = commonAncestor->left;
		}
		else if (commonAncestor->value < min) {
			commonAncestor = commonAncestor->right;
		}
	}

	return commonAncestor->value;
}

void BST::maximumSumPath() { 

	Path max = this->pathSum();
	
	print("Maximum sum path is: ");
	if (!isEmpty()) {
		print(this->value); // print the root

		// print the rest
		if (this->value != max.root) {
			if (max.root < this->value) {
				this->left->printToChild(max.root);
			}
			else {
				this->right->printToChild(max.root);
			}
		}
	}
	print("\n");
}

Path BST::pathSum() {
	if ((!this->left && !this->right)) {
		Path p;
		p.root = this->value;
		p.sum = this->value;
		return p;
	}
	
	Path biggest;
	biggest.root = -1;
	biggest.sum = -1;
	if (this->left && this->right) {
		Path left = this->left->pathSum();
		Path right = this->right->pathSum();

		if (left.sum > right.sum) { 
			biggest.root = left.root; // root of the bigger path is coming from the left
			biggest.sum = left.sum + this->value;
		}
		else {
			biggest.root = right.root;
			biggest.sum = right.sum + this->value;
		}
		return biggest;
	}

	if (this->left) {
		Path left = this->left->pathSum();
		biggest.root = left.root; 
		biggest.sum = left.sum + this->value;
		return biggest;
	}

	if (this->right) { // only possibility but writing the if for clarity
		Path right = this->right->pathSum();
		biggest.root = right.root;
		biggest.sum = right.sum + this->value;
		return biggest;
	}

	return biggest;
}

void BST::maximumWidth() {

	int level = 0;
	int maxLevel = 0;
	int width = nodesInLevel(1);
	int maxWidth = width;

	while (width > 0) {
		++level;
		width = nodesInLevel(level);
		if (width > maxWidth) {
			maxWidth = width;
			maxLevel = level;
		}
	}

	print("Maximum level is: ");
	if (!isEmpty()) {
		printLevel(maxLevel);
		noComma = true;
	}
	print("\n");
}

int BST::nodesInLevel(int level) {
	if (level == 0) {
		return 0;
	}

	if (level == 1) {
		return !isEmpty(); // 1 if not empty, 0 if empty
	}

	int sum = 0;
	if (this->left) {
		sum += this->left->nodesInLevel(level - 1);
	}
	if (this->right) {
		sum += this->right->nodesInLevel(level - 1);
	}

	return sum;
}

void BST::printLevel(int level) {
	if (level < 1) {
		return;
	}

	if (level == 1) {
		if (noComma) { // if the first element, no comma
			print(this->value);
			noComma = false;
		}
		else {
			print(", " << this->value);
		}
	}
	if (this->left) {
		this->left->printLevel(level - 1);
	}
	if (this->right) {
		this->right->printLevel(level - 1);
	}
}

int BST::depth(int key) {
	if ((key < this->value && !this->left) || (key > this->value && !this->right)) { // if key does not exist, depth is negative
		return INT16_MIN;
	}

	if (key == this->value) {
		return 1;
	}

	if (key < this->value && this->left) {
		return 1 + this->left->depth(key);
	}

	if (key > this->value && this->right) {
		return 1 + this->right->depth(key);
	}

	return 0;
}

void BST::pathFromAtoB(int A, int B) { 
	int ancestor = lowestCommon(A, B);
	print("Path from " << A << " to " << B << " is: ");

	if (ancestor < 0) {
		print("\n");
		return;
	}

	BST* pointer = this;

	while (pointer->value != ancestor) {
		if (ancestor < pointer->value) {
			pointer = pointer->left;
		}
		else if (ancestor > pointer->value) {
			pointer = pointer->right;
		}
	}

	pointer->printFromChild(A); // print from child to root (included)

	if (pointer->value != B) { // print from root (excluded) to child
		if (B < pointer->value) {
			pointer->left->printToChild(B);
		}
		else {
			pointer->right->printToChild(B);
		}
	}
	noComma = true;
 	print("\n");
}

void BST::printFromChild(int A) {
	if (this->value == A) {
		if (noComma) {
			print(this->value);
			noComma = false;
		}
		else {
			print(", " << this->value);
		}
		return;
	}

	if (A < this->value) {
		this->left->printFromChild(A);
	}
	else {
		this->right->printFromChild(A);
	}

	print(", " << this->value);
}

void BST::printToChild(int A) {
	if (this->value == A) {
		print(", " << this->value);
		return;
	}

	print(", " << this->value);
	if (A < this->value) {
		this->left->printToChild(A);
	}
	else {
		this->right->printToChild(A);
	}
}

bool BST::isLeaf(int key) {
	if (this->value == key) {
		if (!this->left && !this->right) {
			return true;
		}
		return false;
	}
	
	if (key < this->value && this->left) {
		return this->left->isLeaf(key);
	}

	if (key > this->value && this->right) {
		return this->right->isLeaf(key);
	}
	
	return false;
}

bool BST::isEmpty() {
	return (!this->right && !this->left && (this->value == INT16_MAX));
}

int BST::size() {
	if (isEmpty()) {
		return 0;
	}

	int res = 0;
	if (!this->left && !this->right) {
		return 1;
	}

	if (this->left) {
		res += this->left->size();
	}

	if (this->right) {
		res += this->right->size();
	}

	return res + 1;
}