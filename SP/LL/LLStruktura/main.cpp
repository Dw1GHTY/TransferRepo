//Proba commita
#include "LList.h"
#include <iostream>
using namespace std;


void main()
{	
	LList *list1 = new LList();
	LList* list2 = new LList();
	list1->addToHead(20);
	list1->addToHead(13);
	list1->addToHead(12);
	list1->addToHead(9);
	list1->addToHead(7);
	list1->addToHead(1);

	list1->deleteFrom(7, 5);
	list1->printAll();
	
} 