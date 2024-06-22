#include"DList.h"
#include "DListNode.h"
#include <iostream>
void main()
{
	DList *list1 = new DList();
	DList* list2 = new DList();
	list1->addToHead(24);
	list1->addToHead(15);
	list1->addToHead(12);
	list1->addToHead(6);
	list1->addToHead(5);
	list1->addToHead(4);
	
	list2->addToHead(28);
	list2->addToHead(26);
	list2->addToHead(14);
	list2->addToHead(1);
	list2->addToHead(3);
	list2->addToHead(9);

	list1->printAll();
	std::cout << std::endl;
	list2->printAll();
	
}
