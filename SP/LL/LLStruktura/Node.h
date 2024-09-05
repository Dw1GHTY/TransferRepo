#pragma once
#include <iostream>
using namespace std;
class Node
{
public:
	int info;
	Node *next;
	Node();
	Node(int i);//info
	Node(int i , Node* n);//i je info
	int print();
	bool isEqual(int el);
	~Node();
};

