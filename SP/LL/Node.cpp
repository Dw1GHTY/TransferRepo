#include "Node.h"


Node::Node()
{
	next=NULL;
}

Node::Node(int i) 
{ 
	info = i;
	next=NULL;
}

Node::Node(int i, Node* n)
{
	info = i;
	next = n;
}

int Node::print()
{
	return info;
}

bool Node::isEqual(int el)
{
	return el == this->info;
}

Node::~Node()
{
}
