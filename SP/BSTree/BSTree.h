#pragma once
#include "Stack.h"
#include "BSNode.h"
#include "Queue.h"
class BSTree
{
public:
	BSNode* root;
	long numOfElements;
public:
	BSTree()
	{
		root = nullptr;
		numOfElements = 0;
	}

	~BSTree() { deleteTree(root); }
	void deleteTree(BSNode* p)
	{
		if (p != nullptr)
		{
			deleteTree(p->left);
			deleteTree(p->right);
			numOfElements--;
			delete p;
		}
	}
	bool isEmpty() { return numOfElements==0; }
	void insert(int el);
	BSNode* search(BSNode* p, int el);


	void balance();
	void deleteByCopying(int el);
	void deleteByMerging(int el);
	
	void preorder(BSNode* p);
	void inorder(BSNode* p);
	void postorder(BSNode* p);

	void breadthFirst();
	void iterativePreorder();
	void iterativeInorder();
	void iterativePostorder();


private:
	void balancer(int* data, int first, int last);
	void copyInArray(int* niz, BSNode* p, int* i);


	//ZADACI SA ISPITA ------ SEPTEMBAR 2022. 3.B)
public:
	int countNodesInRange(BSNode* root, int min, int max);	//rekurzivna, broji nodove u intervalu min max.

	//ZADACI SA ISPITA ------- JUN 2022 3. ZADACI
	int countNodes(BSNode* p);
	bool isPerfect();
private: bool isPerfect(BSNode* p);

	//ZADACI SA ISPITA ------- JUN2 2021 3. ZADATAK ---------

public:
	BSNode* findNodeWithLargestRightSubtree();
	BSNode* findNodeWithLargestRightSubtree(BSNode* ptr, BSNode** largest, int* max);

	//ZADACI SA ISPITA ------- OKTOBAR2 2021 3. ZADATAK
	BSNode* getNNode();
	void getNNode(BSNode* ptr, BSNode** retVal, bool* flag);


	//ZADACI SA ISPITA ------- JUNSKI 2021. 3. ZADATAK

	int CountSL();
	int CountSL(BSNode* ptr);
	int Count(BSNode* ptr);
};

