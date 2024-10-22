/**
* Title: Binary Search Tree Header File
* Author : Yunus Celik
* ID: 22203347
* Section : 1
* Homework : 1
* Description : This header file defines the BST class, Path class, and deletePointedNode friend function
*/

#ifndef BST_H
#define BST_H
#include <iostream>

class Path {
public:
	int root;
	int sum;
};

class BST {
private:
	int value;
	BST* left;
	BST* right;

	bool insertKeyNoMessage(int key);
	bool deleteKeyNoMessage(int key);
	int lowestCommon(int A, int B);
	void printLevel(int level);
	void printFromChild(int A);
	void printToChild(int A);
	Path pathSum();
	bool isLevelFull(int level);
	int nodesInLevel(int level);
	void printInorder();
	int inorderSuccessor();
	bool isLeaf(int key);
	int smallest();
	void deleteRoot();
	bool isEmpty();
	int depth(int key);
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
#endif