#include "BST.h"
#define println(x) std::cout << x << std::endl

BST::BST(int keys[], int size) { // what if keys is empty?
		this->left = nullptr;
		this->right = nullptr;
		this->value = INT_MAX; // tree is empty

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

bool BST::insert(int key) {
	if (key < this->value) { 
		if (this->left) {
			return this->left->insert(key);
		}

		this->left = new BST(key);
		return true;
		
	}
	else if (key > this->value) {
		if (this->right) {
			return this->right->insert(key);
		}

		this->right = new BST(key);
		return true;
		
	}

	return false;
	
}

void BST::deleteKey(int key) {
	if (!this || (key < this->value && !this->left) || (key > this->value && !this->right)) {
		println("Key " << key << " is not deleted. It does not exist!");
		return;
	}

	if (key < this->value) {
		if (this->left->value == key) {
			deletePointedNode(this->left); 
			println("Key " << key << " is deleted.");
			return;
		}
		
		this->left->deleteKey(key);
	}
	else if (key > this->value) {
		if (this->right->value == key) {
			deletePointedNode(this->right);
			println("Key " << key << " is deleted.");
			return;
		}

		this->right->deleteKey(key);
	}
	else {
		deleteRoot();
		println("Key " << key << " is deleted.");
	}

}

void deletePointedNode(BST*& node) {
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
		int successor = node->inorderSuccessor();
		node->deleteKey(successor);
		node->value = successor;
	}
}

void BST::deleteRoot() {
	if (!this->left && !this->right) {
		this->value = INT_MAX; // tree is empty
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
		this->value = successor;
		this->right->deleteKey(successor);
	}
}

int BST::inorderSuccessor() {
	if (!this->right) {
		return this->value;
	}

	std::string s = "";
	this->right->inorder(s);

	std::string res = "";
	for (int i = 0; i < s.size() && s[i] != ','; ++i) {
		res += s[i];
	}

	return std::stoi(res); // stoi = string to int
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
	

	BST obj(a, 1);
	obj.displayInorder();
	obj.deleteKey(10);
	obj.displayInorder();
}