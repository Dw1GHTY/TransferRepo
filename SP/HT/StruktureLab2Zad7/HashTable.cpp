#pragma once
#include"HashTable.h"
#include"HashObject.h"
#include "math.h"
#include <iostream>

using namespace std;


HashTable::HashTable()
{
	count = 0;
	length = 0;
	niz = NULL;
}

HashTable::HashTable(int l)
{
	length = l;
	count = 0;
	this->niz = new HashObject[this->length];
}

HashTable::~HashTable() 
{
	if (count > 0)
	{
		for (int i = 0;i < length;i++)
		{
			if (niz[i].getStatus() == 1)
			{
				niz[i].deleteRecord();
			}
		}
		delete[] niz;
	}
}

//hes funkcija
int HashTable::h(HashObject obj)
{
	return (f(obj.getKey()));
}

//primarna transformacija
int HashTable::f(char* macAddress)
{
	/*int result = 0;
	int a = 7;
	for (int i = 0;i < strlen(s);i++)
	{
		result = result << a^s[i];
	}
	return result;*/

	int result = 0;
	for (int i = 0; i < strlen(macAddress); i++) 
	{
		result += macAddress[i] << i;
	}
	result = (result * 11) % length;

	return result;
}

//sekundarna transformacija (h(k) + c(i)) mod length
int HashTable::g(int f_result)
{
	//f_result je rezultat hes funkcije nakon primene primarne transformacije
	
	//for (int i = 0;i < length;i++)
	//{
	//	int vracam = (a + 3 * i) % length;
	//	//da si imao kvadratno trazenje bilo bi:
	//	//vracam=(a+K*i^2);
	//	//pri cemu je K proizvoljna celobrojna konstanta
	//	if (niz[vracam].isFree())
	//		return vracam;
	//}

	//linearna
	/*
	for (int i = 0; i < length; i++) 
	{
		int result = f_result + i;

		if (niz[i].isFree())
			return result;
	}
	*/

	//kvadratna
	for (int i = 0; i < length; i++)
	{
		int result = f_result + pow(i, 2);

		if (niz[i].isFree())
			return result;
	}

	throw "Cela tablica obidjena. Nema vise mesta";
	return -1;
}
void HashTable::insert(HashObject obj)
{
	if (count == length)
		throw "Tablica je puna.";

	int offset = findUnoccupied(obj);
	niz[offset] = obj;
	niz[offset].free = false;
	count++;
}
int HashTable::findUnoccupied(HashObject obj)
{
	int hash = h(obj);
	int probe = hash;
	if (niz[hash].isFree())
	{
		return hash;
	}
	do 
	{
		probe = g(probe);
		if (niz[probe].isFree())
		{
			return probe;
		}
	} while (probe != hash);
	throw "Hes tablica je puna.";
	return 0;
}
int HashTable::findMatch(char* k)
{
	int probe = f(k);
	if (niz[probe].isFree())
	{
		throw "Ne postoji trazeni element.";
	}
	else
	{
		if (niz[probe].isEqualKey(k))
		{
			return probe;
		}
		probe = g(probe);//ako ga nismo nasli idemo na
		//sinonim
		return probe;
	}
	throw "Ne postoji trazeni element.";
	return -1;
}
void HashTable::withdraw(char* s)
{
	if (count == 0)
		throw "Tabela je prazna.";

	int probe = findMatch(s);
	//array[probe].free = true;
	niz[probe].deleteRecord();
	count--;
}
void HashTable::printAll()
{
	if (count == 0)
		throw "Tablica je prazna.";
	cout << "****************Hes Tablica****************\n";
	for (int i = 0;i < length;i++)
	{
		{
			cout << "[" << i << "]" << " " << "->" << " ";
			if (!(niz[i].isFree()))//ako je zazuzet znaci
				//ima elemenata, treba da istampas
			{
				niz[i].print();
			}
			else//ako je slobodan nema sta da stampa
			{
				cout << "X";
			}
			cout << endl;
		}
	}
	cout << "****************************************";

}

bool HashTable::insertOrUpdate(char* macAddress, char* IPaddress) 
{
	HashObject newAddress = HashObject(macAddress, IPaddress);
	int position = h(newAddress);

	if (niz[position].mac == nullptr)
		insert(newAddress);
	else if (niz[position].mac == macAddress)
	{
		if (niz[position].ip != IPaddress) 
		{
			niz[position].ip = IPaddress;
			return true;
		}
		return false;
	}
	else
	{
		//ovde su mac adrese razlicite pa se radi kvadratno trazenje
		//dok se ne nadje slobodno mesto
		return true;
	}
}