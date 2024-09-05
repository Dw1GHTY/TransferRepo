#pragma once
#include "Node.h"
class LList
{
protected:
	Node *head, *tail;
public:
	LList();
	~LList();
	bool isEmpty();
	void addToHead(int el);
	void addToTail(int el);
	int deleteFromHead();
	int deleteFromTail();
	Node* findNodePtr(int el);
	Node* getHead();
	Node* getNext(Node* ptr);
	int getHeadEl();
	int getNextEl(int el);
	void printAll();
	bool isInList(int el);
	void deleteEl(int el);
	Node* removeNodeFromHead();
	int nodeToNumber(Node* ptr);
	void injectOrRemove(int br);
	LList* extractEven();
	void Update(int value, int add);
	void update(int value, int add);
	void GroupElements();
	LList* SplitOrMove();
	void fillMissingItems();
	void deleteFrom(int val, int noToDelete);
	void Exchange(LList& lista, int val, int length);
	LList* FormList(int* array);
};

