#ifndef BST_H
#define BST_H

class BST {
private:
	int value;
	BST* left;
	BST* right;
public:
	BST(int keys[], int size);
	~BST();
	void insertKey(int key);
	void deleteKey(int key);
	void displayInorder();
	void findFullBTLevel();
	void lowestCommonAncestor(int A, int B);
	void maximumSumPath();
	void maximumWidth();
	void pathFromAtoB(int A, int B);
};

#endif BST_H