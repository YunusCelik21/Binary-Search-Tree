#include "BST.h"
#define println(x) std::cout << x << std::endl

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

bool BST::insertKeyNoMessage(int key) {
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

bool BST::deleteKeyNoMessage(int key) {
	if ((key < this->value && !this->left) || (key > this->value && !this->right)) {
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

	return false;
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
		this->value = INT16_MIN; // tree is empty now
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
	
	println("Inorder display is: " << result.substr(0, result.size() - 2));
}

void BST::inorder(std::string& result) {
	if (this->left) {
		this->left->inorder(result);
	}
		result += std::to_string(this->value) + ", ";
	if (this->right) {
		this->right->inorder(result);
	}
}

void BST::findFullBTLevel() { // CANNOT USE ARRAY
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

void BST::lowestCommonAncestor(int A, int B) { // STRING
	int* rootToA = rootToKey(A);
	int* rootToB = rootToKey(B);
	int min = std::min(depth(A), depth(B));
	std::string commonAncestor = "";

	for (int i = 0; i < min && rootToA[i] == rootToB[i]; ++i) { // while they have the same path from the root, continue
		commonAncestor = std::to_string(rootToA[i]);
	}

	println("Lowest common ancestor of " << A << " and " << B << " is: " << commonAncestor);

	delete[] rootToA;
	delete[] rootToB;
}

void BST::maximumSumPath() { // ARRAY, STRING
	int size = this->size();
	int* keys = new int[size];
	std::string res = "";
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

	int maxSum = INT16_MIN;
	int maxSumLeaf = INT16_MIN;
	for (int i = 0; i < size; ++i) {
		if (isLeaf(keys[i])) {
			int sum = pathSum(keys[i]);

			if (sum > maxSum) {
				maxSum = sum;
				maxSumLeaf = keys[i];
			}
		}
	}

	delete[] keys;
	println("Maximum sum path is: " << pathFromAtoBNoMessage(this->value, maxSumLeaf));

}

int BST::pathSum(int key) { 
	int* path = rootToKey(key);
	int sum = 0;

	for (int i = 0; i < depth(key); ++i) {
		sum += path[i];
	}

	delete[] path;
	return sum;
}

void BST::maximumWidth() { // ARRAY, STRING
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
	std::string res = pathFromAtoBNoMessage(A, B);

	println("Path from " << A << " to " << B << " is: " << res);
} 

std::string BST::pathFromAtoBNoMessage(int A, int B) {
	int* rootToA = rootToKey(A);
	int* rootToB = rootToKey(B);
	int min = std::min(depth(A), depth(B));
	std::string res = "";

	if (isEmpty() || min < 0) { // if there is no path
		return res;
	}

	int commonAncestor = INT16_MAX;

	for (int i = 0; i < min && rootToA[i] == rootToB[i]; ++i) { // while they have the same path from the root, continue
		commonAncestor = rootToA[i];
	}

	// path from A to common ancestor
	int i;
	for (i = depth(A) - 1; i >= 0 && rootToA[i] != commonAncestor; --i) {
		res += std::to_string(rootToA[i]) + ", ";
	}

	// path from common ancestor to B
	for (i; i < depth(B); ++i) {
		res += std::to_string(rootToB[i]) + ", ";
	}

	res = res.substr(0, res.size() - 2);

	delete[] rootToA;
	delete[] rootToB;

	return res;
}

int* BST::rootToKey(int key) { // does not delete the path, caller should do it
	int length = depth(key);
	if (length < 0) {
		return nullptr;
	}

	int* path = new int[length];
	BST* pointer = this;

	for (int i = 0; i < length; ++i) {
		path[i] = pointer->value;
		
		if (key < pointer->value) {
			pointer = pointer->left;
		}
		else if (key > pointer->value) {
			pointer = pointer->right;
		}
	}
	return path;
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

int main() {
	int a[] = {10, 7, 20, 5, 15, 21, 2, 12, 18, 24, 3, 19};

	
	
	obj.isLevelFull(6);
	obj.isLevelFull(7);
	obj.deleteKey(1);
	obj.findFullBTLevel();
	obj.lowestCommonAncestor(3, 9);
	obj.lowestCommonAncestor(12, 15);
	obj.maximumSumPath();
	obj.maximumWidth();
	obj.pathFromAtoB(2, 21);
	obj.insertKey(8);
	obj.insertKey(7);
	obj.deleteKey(10);
	obj.deleteKey(11);
	obj.displayInorder();
}