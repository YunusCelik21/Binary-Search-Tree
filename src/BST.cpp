#include "BST.h"
#define println(x) std::cout << x << std::endl
#define print(x) std::cout << x

static bool noComma = true;

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
	
	return this->right->smallest();
}

int BST::smallest() {
	if (!this->left) {
		return this->value;
	}

	return this->left->smallest();
}

void BST::displayInorder() {
	
	print("Inorder display is: ");
	printInorder();
	print("\n");
	noComma = true;
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

void BST::lowestCommonAncestor(int A, int B) {
	int res = lowestCommon(A, B);
	if (res < 0) {
		println("error message"); // TODO:
	}
	
	println("Lowest common ancestor of " << A << " and " << B << " is: " << res);
}

int BST::lowestCommon(int A, int B) {
	if (depth(A) < 0 || depth(B) < 0) {
		return -1; // no lowest common
	}
	int min = A < B ? A : B;
	int max = A > B ? A : B;

	BST* commonAncestor = this;
	while (!(commonAncestor->value <= max && commonAncestor->value >= min)) {
		if (commonAncestor->value > max) {
			commonAncestor = commonAncestor->left;
		}
		else if (commonAncestor->value < min) {
			commonAncestor = commonAncestor->right;
		}
	}

	return commonAncestor->value;
}

void BST::maximumSumPath() { // ARRAY, STRING
	int size = this->size();
	int* keys = new int[size];
	std::string res = "";
	std::string s = "";

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

int BST::pathSum(int key) { // PROBLEM
	int* path = rootToKey(key);
	int sum = 0;

	for (int i = 0; i < depth(key); ++i) {
		sum += path[i];
	}

	delete[] path;
	return sum;
}

void BST::maximumWidth() {
	if (isEmpty()) {
		println("Maximum level is: ");
	}

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
	printLevel(maxLevel);
	print("\n");
	noComma = true; // next method's message should start with no comma
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

	this->left->printLevel(level - 1);
	this->right->printLevel(level - 1);
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
	if (ancestor < 0) {
		println("Error"); // TODO:
	}

	int min = A < B ? A : B;
	int max = A > B ? A : B;
	BST* pointer = this;

	while (pointer->value != ancestor) {
		if (ancestor < pointer->value) {
			pointer = pointer->left;
		}
		else if (ancestor > pointer->value) {
			pointer = pointer->right;
		}
	}

	print("Path from " << A << " to " << B << " is: ");
	pointer->printFromChild(A);
	if (pointer->value != B) {
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

std::string BST::pathFromAtoBNoMessage(int A, int B) { // PROBLEM
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

int* BST::rootToKey(int key) { // PROBLEM
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
	int a[] = {10, 7, 20, 5, 9, 15, 21, 2, 12, 18, 24, 3, 19};

	BST obj(a, 13);
	
	obj.printFromChild(3);
	println("------");
	obj.printToChild(19);
	println("------");
	obj.displayInorder();
	obj.findFullBTLevel();
	obj.deleteKey(1);
	obj.findFullBTLevel();
	obj.lowestCommonAncestor(3, 9);
	obj.lowestCommonAncestor(12, 15);
	obj.maximumWidth();
	obj.pathFromAtoB(2, 21);
	obj.pathFromAtoB(3, 19);
	obj.pathFromAtoB(12, 20);
	obj.pathFromAtoB(20, 12);
	obj.pathFromAtoB(20, 20);
	obj.insertKey(8);
	obj.insertKey(7);
	obj.deleteKey(10);
	obj.deleteKey(11);
	obj.deleteKey(20);
	obj.displayInorder();

}