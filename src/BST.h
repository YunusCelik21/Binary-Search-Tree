#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>

class BST {
private:
	int value;
	BST* left;
	BST* right;

	bool insertKeyNoMessage(int key);
	bool deleteKeyNoMessage(int key);
	std::string pathFromAtoBNoMessage(int A, int B);
	int pathSum(int key);
	int* rootToKey(int key);
	void inorder(std::string& string);
	int depth(int key);
	bool isLeaf(int key);
	int inorderSuccessor();
	void deleteRoot();
	bool isEmpty();
	int size();

public:
	bool isLevelFull(int level);

	BST(int keys[], int size);
	BST(int value);
	~BST();
	void insertKey(int key); 
	void deleteKey(int key);
	void displayInorder();
	void findFullBTLevel();
	void lowestCommonAncestor(int A, int B);
	void maximumSumPath();
	void maximumWidth();
	void pathFromAtoB(int A, int B);

	friend void deletePointedNode(BST*& node);
};
#endif