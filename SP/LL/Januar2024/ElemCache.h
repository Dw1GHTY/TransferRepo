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
		Elem* p = tail;	//poslednji u listi
		if (count == cntMax)	//brisanje sa kraja i dodavanje na njega 
		{
			tail = p->prev;
			p->prev->next = p->next;
			
			//dodavanje novog
			elem->next = p->next;
			elem->prev = p->prev;
			Delete(p);
		}
		else 
		{
			elem->next = p->next;
			elem->prev = p;
			p->next = elem;
		}

	}

	Elem* get(int key)
	{
		Elem* current = head;	//prvi elemnt u listi
		do//dok nije jednak tail, jer tail ukazuje na poslednji	
		{
			if (current->key == key) 
			{
				//el je prvi u list
				if (head == current)
					return current;
				//el je poslednji u listi
				if (tail == current) 
				{
					//spajanje tail sa pretposlednjim
					current->prev->next = current->next;
					tail = current->prev;
					//spajanje pronadjenog el sa head i prvim
					current->next = head;
					current->prev = head->prev;
					head->prev = current;
					head = current;
				}
				else //el je izmedju dva el 
				{
					//prelancavanje SUSJEDA
					current->prev->next = current->next;
					current->next->prev = current->prev;
					//prelancavanje na pocetak
					current->next = head;
					current->prev = head->prev;
					head->prev = current;
					head = current;
				}
				
				return current;	//vraca el
			}
			else
			{
				cout << "element nije u Cache-u";
				return nullptr;
			}
		} while (current != tail);
	}

	void Delete(Elem* e)
	{
		e->prev = nullptr;
		e->next = nullptr;
		e->key = NULL;
	}
};