#include "BST.h"
#include <iostream>

BST::BST(int keys[], int size) {
	if (size != 0) {
		this->left = nullptr;
		this->right = nullptr;
		this->value = keys[0];

		for (int i = 1; i < size; ++i) {
			this->insertKey(keys[i]);
		}
	}
	else {
		// ?
	}
}

BST::~BST() {
}

void BST::insertKey(int key) {
	int arr[] = {key};

	if (key <= this->value) { // assumed there won't be any identical keys
		if (this->left) {
			this->left->insertKey(key);
		}
		else {
			this->left = new BST(arr, 1);
		}
	}
	else {
		if (this->right) {
			this->right->insertKey(key);
		}
		else {
			this->right = new BST(arr, 1);
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