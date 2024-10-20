#include "BST.h"
#define println(x) std::cout << x << std::endl

BST::BST(int keys[], int size) { // what if keys is empty?
		this->left = nullptr;
		this->right = nullptr;
		this->value = 0;

	if (size != 0) {
		this->value = keys[0];

		for (int i = 1; i < size; ++i) {
			this->insert(keys[i]);
		}
	}

	println("BST with size " << size << " is created.");
}

BST::BST(int value) : value(value), left(nullptr), right(nullptr) {}

BST::~BST() {

}

void BST::insertKey(int key) {
	if (insert(key)) {
		println("Key " << key << " is added.");
	}
	else {
		println("Key " << key << " is not added. It exists!");
	}
}

void BST::deleteKey(int key) {
	if (!this) {
		println("Key " << key << " is not deleted. It does not exist!");
		return;
	}

	if (this->value < key) {
		if (this->left->value == key) {
			
		}
		
		this->left->deleteKey(key);
	}
	else if (this->value > key) {
		if (this->right->value == key) {

		}

		this->right->deleteKey(key);
	}
	else {

	}

}

void BST::displayInorder() {
	std::string result = "";
	if (this) {
		this->left->inorder(result);
		result += std::to_string(this->value) + ", ";
		this->right->inorder(result);
	}

	
	println("Result: " << result.substr(0, result.size() - 2));
}

void BST::inorder(std::string& result) {
	if (this) {
		this->left->inorder(result);
		result += std::to_string(this->value) + ", ";
		this->right->inorder(result);
	}
}

bool BST::insert(int key) {
	if (key < this->value) { 
		if (this->left) {
			this->left->insert(key);
		}
		else {
			this->left = new BST(key);
			return true;
		}
	}
	else if (key > this->value) {
		if (this->right) {
			this->right->insert(key);
		}
		else {
			this->right = new BST(key);
			return true;
		}
	}
	else {
		return false;
	}
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
	int a[] = { 10, 7, 20, 5, 9, 15, 21, 2, 12, 18, 24, 3, 19 };
	BST obj(a, 13);
	obj.displayInorder();
	obj.insertKey(8);
	obj.insertKey(7);

}