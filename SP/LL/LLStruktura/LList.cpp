#include "LList.h"


LList::LList()
{
	head=NULL;
}


LList::~LList()
{
	while(!isEmpty())
	{
		int tmp = deleteFromHead();
	}
}


bool LList::isEmpty()
{
	return head==NULL;
}

void LList::addToHead(int el)
{
	head = new Node(el, head);
}

void LList::addToTail(int el)
{
	if(!isEmpty())
	{
		Node* tmp = head;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new Node(el);
	}
	else
		addToHead(el);
}

int LList::deleteFromHead()
{
	if(isEmpty())
		throw new exception("List is empty");
	int el = head->info;
	Node *tmp = head;
	head = head->next;
	delete tmp;
	return el;
}

int LList::deleteFromTail()
{
	if(isEmpty())
		throw new exception("List is empty");
	int el;
	if (head->next == NULL)
	{
		el = head->info;
		delete head;
		head = NULL;
	}
	else
	{
		Node* prev = head;
		Node *tmp = head;
		while (tmp->next != NULL)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		el = tmp->info;
		delete tmp;
		prev->next = NULL;
	}
	return el;
}

Node* LList::findNodePtr(int el)
{
	if(isEmpty())
		throw new exception("List is empty");
	Node *ret = head;
	while(ret!=NULL && ret->info!=el)
	{
		ret = ret->next;
	}
	return ret;
}
int LList::nodeToNumber(Node* ptr)
{
	Node *el = head;
	while (el != ptr && el!= NULL)
	{
		el = el->next;
	}
	return el->info;

}

Node* LList::getHead()
{
	return head;
}

Node* LList::getNext(Node* ptr)
{
	if(isEmpty())
		throw new exception("List is empty");
	return ptr->next;
}

int LList::getHeadEl()
{
	if(isEmpty())
		throw new exception("List is empty");
	return head->info;
}

int LList::getNextEl(int el)
{
	if(isEmpty())
		throw new exception("List is empty");
	Node* tmp = findNodePtr(el);
	if(tmp==NULL)
		throw new exception("Node doesn't exist");
	if(tmp->next == NULL)
		throw new exception("Element doesn't have next node");
	return tmp->next->info;
}

void LList::printAll()
{
	Node *tmp = head;
	while(tmp!=NULL)
	{
		cout<<tmp->print() << " ";
		tmp=tmp->next;
	}
	cout << endl;
}

bool LList::isInList(int el)
{
	if(isEmpty())
		return false;
	Node* tmp = findNodePtr(el);
	if(tmp==NULL)
		return false;
	else
		return true;
}

void LList::deleteEl(int el)
{
	if (!isEmpty())
		throw new exception("list is empty");

	if (head->isEqual(el)) 
	{
		Node *tmp = head;
		head = head->next;
		delete tmp;
	}
	else 
	{
		Node *pred, *tmp; 
		for (pred = head, tmp = head->next; tmp != NULL && !(tmp->isEqual(el));
			  pred = pred->next, tmp = tmp->next);
		if (tmp != NULL) 
		{
			pred->next = tmp->next;
			delete tmp;
		}
    }
}

Node* LList::removeNodeFromHead()
{
	if(isEmpty())
		return NULL;
	Node *tmp = head;
	head = head->next;
	return tmp;
}
void LList:: injectOrRemove(int br)
{
	Node* tmp = head;
	Node* prev = NULL;
	while (tmp != NULL && br > tmp->info)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		Node* novi = new Node(br,NULL);
		prev->next = novi;
	}
	else if (tmp == head && tmp->info!=br)
	{
		Node* novi = new Node(br, tmp);
		head = novi;
	}
	else if (tmp == head)
	{
		head = head->next;
		delete tmp;
	}
	else if (tmp->info != br)
	{
		Node* novi = new Node(br, tmp);
		prev->next = novi;
	}
	else
	{
		prev->next = tmp->next;
		delete tmp;
	}
}
LList* LList::extractEven()
{
	Node* tmp = head;
	Node* prev = NULL;
	Node* tmp2 = NULL;
	LList* lista1 = new LList();
	for (tmp; tmp != NULL; prev = tmp, tmp = tmp->next)
	{
		if (tmp->info % 2 == 0)
		{
			if (lista1->isEmpty())
			{
				lista1->addToHead(tmp->info);
				tmp2 = lista1->head;
			}
			else
			{
				Node* novi = new Node(tmp->info, NULL);
				tmp2->next = novi;
				tmp2 = novi;
			}
			if (tmp == head)
			{
				head = head->next;
			}
			else
			{
				prev->next = tmp->next;
			}
		}
	}
	return lista1;
}
void LList::Update(int value, int add)
{
	Node* tmp = head;
	Node* ptr = NULL;
	Node* prev = head;
	Node* prev2 = NULL;
	while (tmp != NULL && !ptr)
	{

		if (tmp->info == value)
		{

			tmp->info = add + value;
			ptr = tmp;
			Node* ptrNext = tmp->next;

			if (tmp->next == NULL)
			{
				return;
			}

			while (ptr->info > tmp->next->info && tmp->next->next!= NULL)
			{
				prev2 = tmp;
				tmp = tmp->next;
			}
			if (tmp->next && ptr != head && tmp->next->next!=NULL)
			{
				ptr->next = tmp->next;
				tmp->next = ptr;
				prev->next = ptrNext;
			}
			else if (tmp == head && ptr == tmp)
			{
				return;
			}
			else if (ptr == head && tmp != ptr &&tmp->next!=NULL)
			{
				head = ptr->next;
				ptr->next = tmp->next;
				tmp->next = ptr;
			}
			else if ( tmp->next->next == NULL && ptr->info > tmp->next->info)
			{
				prev->next = ptr->next;
				tmp->next->next = ptr;
				ptr->next = NULL;
			}
			else if (tmp->next->next == NULL && ptr->info < tmp->next->info)
			{
				prev->next = ptr->next;
				ptr->next = tmp->next;
				tmp->next = ptr;
			}
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void LList::GroupElements()
{

	Node* tmp = head;
	Node* ptr = NULL;
	Node* prev = NULL;
	Node* nextTmp = NULL;
	while (tmp != NULL)
	{
		nextTmp = tmp->next;
		prev = tmp;
		ptr = tmp->next;
		while (ptr != NULL)
		{
			if (tmp->info == ptr->info)
			{
				if (tmp->next->info != ptr->info)
				{
					tmp->next = ptr;
					prev->next = ptr->next;
					ptr->next = nextTmp;
				}				
			}
			prev = ptr;
			ptr = ptr->next;
		}
		tmp = tmp->next;
	}

}
 LList* LList :: SplitOrMove()
{
	 LList* lista = new LList();
	 Node* tmp = head;
	 Node* ptr = NULL;
	 Node* prev = NULL;
	 bool nadjen = false;
	 while (tmp!= NULL)
	 {
		 prev = tmp;
		 ptr = tmp->next;
		 while (ptr != NULL)
		 {
			 
			 if (ptr->info == tmp->info)
			 {				 
				 nadjen = true;
				 lista->addToHead(ptr->info);
				 prev->next = ptr->next;
			 }
			 prev = ptr;
			 ptr = ptr->next;
		 }
		 if (!nadjen)
		 {
			 if (tmp == head)
			 {
				 head = head->next;				
			 }
			 else
			 {
				 prev->next = tmp->next;
			 }
			 lista->addToHead(tmp->info);
		 }
		 tmp = tmp->next;
	 }
	 return lista;
}
 void LList::fillMissingItems()
 {
	 Node* tmp = head;
	 Node* prev = NULL;
	 while (tmp != NULL && tmp->info <= 100)
	 {
		 while (head->info < 0)
		 {
			 head = head->next;
		 }
		 if (head->info != 0)
		 {
			 addToHead(0);
			 prev = head;
			 while (prev->info + 1 < prev->next->info && prev->info<100)
			 {
				 Node* novi = new Node(prev->info + 1, prev->next);
				 prev->next = novi;
				 prev = novi;
			 }
		 }
		 else
		 {
			 prev = tmp;
			 while (tmp->next && prev->info + 1 < tmp->next->info && prev->info < 100)
			 {
				 Node* novi = new Node(prev->info + 1, tmp->next);
				 prev->next = novi;
				 prev = novi;
			 }
			 tmp = tmp->next;
		 }		 
	 }
	 if (!tmp && prev->info < 100)
	 {
		 while (prev->info + 1 <= 100)
		 {
			 Node* novi = new Node(prev->info + 1,NULL);
			 prev->next = novi;
			 prev = novi;
		 }
	 }
	 if (tmp && tmp->info >100)
	 {
		 prev->next = NULL;
	 }	
 }
 void LList::deleteFrom(int val, int noToDelete)
 {
	 Node* tmp = head;
	 Node* prev = NULL,*ptr=NULL;
	 while (tmp != NULL && tmp->info != val)
	 {
		 prev = tmp;
		 tmp = tmp->next;
	 }
	/* ptr = prev;
	 int i = 0;
	 for (i; i < noToDelete; i++)
	 {
		 prev = tmp;
		 tmp = tmp->next;
		 delete prev;
	 }
	 if (!ptr)
		 head = tmp;
	 else
		 ptr->next = tmp;*/

	 /*if (tmp->info == val)
	 {
		 int i = 0;
		 if (tmp == head )
		 {
			 while (tmp && i < noToDelete)
			 {
				 head = head->next;
				 i++;
			 }
		 }
		 else
		 {
			 while (tmp != NULL && i < noToDelete)
			 {
				 prev->next = tmp->next;
				 tmp = tmp->next;
				 i++;
			 }
		 }
	 }*/
 }
 void LList::Exchange(LList& lista, int val, int length)
 {
	 Node* p1 = head;
	 Node* p2 = lista.head;
	 Node* t1 = head;
	 Node* t2 = lista.head;
	 Node* r1 = NULL;
	 Node* r2 = NULL; 
	 bool nadjen = false;
	 while (!nadjen)
	 {
		 if (t1->info == val)
		 {
			 nadjen = true;
			 while (t1 != NULL && t2 != NULL && --length>0)
			 {
				 t1 = t1->next;
				 t2 = t2->next;
			 }
			 r1 = t1;
			 r2 = t2;
			 t1 = p1;
			 t2 = p2;
			 if (val == head->info)
			 {
				 p1 = r1->next;
				 p2 = r2->next;
				 head = t2;
				 lista.head = t1;			 
			 }
			 else
			 {
				 t1 = p1->next;
				 t2 = p2->next;
				 p1->next = t2;
				 p2->next = t1;
				 p1 = r1->next;
				 p2 = r2->next;								
			 }
			 r1->next = p2;
			 r2->next = p1;
		 }
		 else
		 {
			 p1 = t1;
			 p2 = t2;
			 t1 = t1->next;
			 t2 = t2->next;
		 }
	 }
 }
 LList* LList::FormList(int* array)
 {
	 LList* lista = new LList();
	 Node* tmp = NULL;
	 int min=array[0];
	 int min1=array[0];
	 for (int i = 0; i<9; i++)
	 {
		 min = array[i];
		 int j=i+1;
		 for (j; j<10 ; j++)
		 {
			 if (min > array[j] && min>=min1)
			 {
				 min1 = array[i];
				 min = array[j];
				 array[i] = min;
				 array[j] = min1;
			 }
		 }	 
		 if (lista->isEmpty())
		 {
			 lista->addToHead(min);
			 tmp = lista->head;
		 }
		 else
		 {
			 Node* novi = new Node(min, NULL);
			 tmp->next = novi;
			 tmp = novi;
		 }
	 }
	 return lista;
 }

