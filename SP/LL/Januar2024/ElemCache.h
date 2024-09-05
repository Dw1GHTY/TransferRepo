#pragma once
#include "Elem.h";


class ElemCache 
{
public:
	Elem* head;
	Elem* tail;
	static int cntMax;
	static int count;

	ElemCache(int size) 
	{
		this->cntMax = size;
		this->count = 0;
		this->head = nullptr;
		this->tail = nullptr;
	}

	void add(Elem* elem) 
	{
		if (count == cntMax) 
		{
			Elem* last = tail->prev;
			elem->prev = last->prev;
			elem->next = last->next;
			last->prev->next = elem;	//predzadnji->next = elem
			last->next->prev = elem;	//tail->prev = elem
			Delete(last);
		}
		else 
		{	
			//add to tail
			elem->prev = tail->prev;
			elem->next = tail;
			tail->prev->next = elem;
			tail->prev = elem;
			count++;
		}

	}

	Elem* get(int key) 
	{
		Elem* current = head;
		while (current->next != tail) 
		{
			if (current->key == key) 
			{
				//prelancati na pocetak
				if (current->prev == head)
					return current;
				else if (current->next == tail)	//ako je poslednji 
				{
					current->prev->next = tail;
					tail->prev = current->prev;
					//prelancavanje na pocetak
					current->next = head->next;
					current->prev = head;
					head->next->prev = current;
					head->next = current;
					return current; 
				}
				else //ako je izmedju dva
				{
					//prelancavanje levog i desnog suseda
					current->prev->next = current->next;
					current->next->prev = current->prev;
					//prelancavanje na head
					current->next = head->next;
					current->prev = head;
					head->next->prev = current;
					head->next = current;
					return current;
				}
			}
			current = current->next;
		}
		cout << "Elem sa vrednoscu " << key << "ne postoji u listi";
		return nullptr;
	}

	void Delete(Elem* e) 
	{
		e->prev = nullptr;
		e->next = nullptr;
		e->key = NULL;
	}
};