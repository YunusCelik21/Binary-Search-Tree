#include "BST.h"
#include <iostream>
#define print(x) std::cout << x << std::endl

BST::BST(int keys[], int size) {
		this->left = nullptr;
		this->right = nullptr;
		this->value = 0;

	if (size != 0) {
		this->value = keys[0];

		for (int i = 1; i < size; ++i) {
			this->insertKey(keys[i]);
		}
	}

	print("BST with size " << size << " is created.");
}

BST::BST(int value) : value(value), left(nullptr), right(nullptr) {}

BST::~BST() {
}

void BST::insertKey(int key) {
	if (key <= this->value) { // assumed there won't be any identical keys
		if (this->left) {
			this->left->insertKey(key);
		}
		else {
			this->left = new BST(key);
		}
	}
	else {
		if (this->right) {
			this->right->insertKey(key);
		}
		else {
			this->right = new BST(key);
		}
	}
}

void BST::deleteKey(int key) {
}

void BST::displayInorder() {
}

void BST::findFullBTLevel() {
}

void BST::lowestCommonAncestor(int A, int B) {
}

void BST::maximumSumPath() {
}

void BST::maximumWidth() {
}

void BST::pathFromAtoB(int A, int B) {
}

int main() {
	int a[] = { 1,2,3 };
	BST obj(a, 3);

}