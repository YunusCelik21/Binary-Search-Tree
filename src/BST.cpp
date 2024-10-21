#include "BST.h"
#define println(x) std::cout << x << std::endl

BST::BST(int keys[], int size) { 
		this->left = nullptr;
		this->right = nullptr;
		this->value = INT_MAX; // tree is empty

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

bool BST::insertKeyNoMessage(int key) {
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

bool BST::deleteKeyNoMessage(int key) {
	if (!this || (key < this->value && !this->left) || (key > this->value && !this->right)) {
		return false;
	}

	if (key < this->value) {
		if (this->left->value == key) {
			deletePointedNode(this->left);
			return true;
		}

		this->left->deleteKeyNoMessage(key);
	}
	else if (key > this->value) {
		if (this->right->value == key) {
			deletePointedNode(this->right);
			return true;
		}

		this->right->deleteKeyNoMessage(key);
	}
	else {
		deleteRoot();
		return true;
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
		node->deleteRoot();
	}
}

void BST::deleteRoot() { // deleting root is a special case
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
		this->deleteKeyNoMessage(successor);
		this->value = successor;
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
	inorder(result);
	
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
	if (isEmpty()) {
		println("Full binary tree level is: 0");
		return;
	}

	BST* pointer = this;
	BST** stack = new BST*[size()];
	int top = 0;
	int res = 1;

	stack[top] = pointer;
	++top;

	while (top != 0) { // while stack is not empty
		BST** arr = new BST*[top];
		int i = 0;
		
		while (top != 0) {
			arr[i] = stack[top - 1];
			++i;
			--top;

			// if any of the nodes doesn't have any of its children, we are in the last full level 
			if (!arr[i - 1]->left || !arr[i - 1]->right) {
				println("Full binary tree level is: " << res);
				delete[] stack;
				delete[] arr;
				return;
			}
		}

		++res; // every node has both its children, continue with the next level

		// push the next level to the stack
		while (i != 0) {
			stack[top] = arr[i - 1]->left;
			++top;
			stack[top] = arr[i - 1]->right;
			++top;
			--i;
		}

		delete[] arr;
	}	
	
	delete[] stack;
}

void BST::lowestCommonAncestor(int A, int B) {

}

void BST::maximumSumPath() {
}

void BST::maximumWidth() {
	if (isEmpty()) {
		println("Maximum level is: ");
	}

	int size = this->size();
	int* width = new int[size + 1]; // width[i] contains the number of nodes at level i

	int* keys = new int[size]; // contains the keys

	std::string s = ""; 
	inorder(s);
	
	// fill the keys array
	for (int i = 0; i < size; ++i) {
		std::string num = "";
		
		int j;
		for (j = 0; j < s.size() && s[j] != ','; ++j) {
			num += s[j];
		}

		keys[i] = std::stoi(num);
		s = s.substr(j + 2, s.size() - (j + 2));
	}

	// initialize the width array
	for (int i = 0; i < size + 1; ++i) {
		width[i] = 0;
	}
	
	// fill the width array
	for (int i = 0; i < size; ++i) { 
		int level = depth(keys[i]);
		width[level]++;
	}

	// find the maximum level
	int maxLevel = 1;
	for (int i = 1; i < size + 1; ++i) {
		if (width[i] > width[maxLevel]) {
			maxLevel = i;
		}
	}

	// list the nodes in the max level
	std::string maxLevelKeys = "";
	for (int i = 0; i < size; ++i) {
		if (depth(keys[i]) == maxLevel) {
			maxLevelKeys += std::to_string(keys[i]) + ", ";
		}
	}

	delete[] width;
	delete[] keys;

	maxLevelKeys = maxLevelKeys.substr(0, maxLevelKeys.size() - 2);
	println("Maximum level is: " << maxLevelKeys);
}

int BST::depth(int key) {
	if (!this || (key < this->value && !this->left) || (key > this->value && !this->right)) { // if key does not exist
		return 0;
	}

	int depth = 0;
	if (key == this->value) {
		return 1;
	}

	if (key < this->value) {
		return 1 + this->left->depth(key);
	}

	if (key > this->value) {
		return 1 + this->right->depth(key);
	}
}

void BST::pathFromAtoB(int A, int B) {
	
}

bool BST::isEmpty() {
	return (!this->right && !this->left && (this->value == INT_MAX));
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

int main() {
	int a[] = { 10, 7, 20, 5, 9, 15, 21, 2, 12, 18, 24, 3, 19 };
	
	BST obj(a, 13);
	obj.displayInorder();
	obj.findFullBTLevel();

	for (int i = 0; i < 13; ++i) {
		println(obj.depth(a[i]));
	}

	std::string s = "";
	obj.inorder(s);
	println(s);
	obj.maximumWidth();
}