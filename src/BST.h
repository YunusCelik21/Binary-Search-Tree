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
	void inorder(std::string& string);
	int inorderSuccessor();
	void deleteRoot();
	bool isEmpty();
	int size();

public:
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
#endif BST_H