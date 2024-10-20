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

}

void BST::displayInorder() {
	std::string result = "";
	if (this) {
		this->left->inorder(result);
		result += this->value + ", ";
		this->right->inorder(result);
	}
}

void BST::inorder(std::string& string) {

}

bool BST::insert(int key) {
	if (key < this->value) { // assumed there won't be any identical keys
		if (this->left) {
			this->left->insertKey(key);
		}
		else {
			this->left = new BST(key);
			return true;
		}
	}
	else if (key > this->value) {
		if (this->right) {
			this->right->insertKey(key);
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
	int a[] = { 1,2,3 };
	BST obj(a, 3);


}