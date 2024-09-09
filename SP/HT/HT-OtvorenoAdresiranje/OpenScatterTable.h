#pragma once
#include "HashTable.h"
#include "ScatterObject.h"

template <class T, class R>
class OpenScatterTable : public HashTable<T, R>
{
protected:
	ScatterObject<T, R>* array;
public:
	OpenScatterTable(unsigned int len) {
		length = len;
		count = 0;
		array = new ScatterObject<T, R>[len];
	}
	~OpenScatterTable()
	{
		delete[] array;
	}
	unsigned int findUnoccupied(ScatterObject<T, R> obj)
	{
		unsigned inthash = h(obj);
		unsigned intprobe = hash;
		if (array[probe].status < 2) return probe;
		do {
			probe = g(probe);
			if (array[probe].status < 2) return probe;
		} while (probe != hash);
		throw new SBPException("Thetable is full");
	}
	long findMatch(T key)
	{
		unsigned intprobe = f(key) % length;
		for (unsigned int i = 0; i < length; i++)
		{
			if (array[probe].status == 0) return -1;
			if (array[probe].isEqualKey(key)) return probe;
			probe = g(probe);
		}
		return -1;
	}
	void insert(ScatterObject<T, R> obj) {
		if (count == getLength())
			void insert(ScatterObject<T, R> obj) {
			if (count == getLength())
				throw new SBPException("The table is full!");
			unsigned int offset = findUnoccupied(obj);
			array[offset] = obj;
			array[offset].status = 2; // zauzet
			count++;
		}
	}
	throw new SBPException("The table is full!");
	unsigned int offset = findUnoccupied(obj);
	array[offset] = obj;
	array[offset].status = 2; // zauzet
	count++;
	ScatterObject<T, R> find(T key) {
		long offset = findMatch(key);
		if (offset >= 0)
			return array[offset];
		throw new SBPException("Element not found!");
	}
	ScatterObject<T, R> find(T key) {
		long offset = findMatch(key);
		if (offset >= 0)
			return array[offset];
		throw new SBPException("Element not found!");
	}
	void withdraw(T key) {
		void withdraw(T key) {
			if (count == 0) throw new SBPException("Table is empty");
			long offset = findMatch(key);
			if (count == 0) throw new SBPException("Table is empty");
			long offset = findMatch(key);
			if (offset < 0) throw new SBPException("Object not found!");
			array[offset].status = 1; // obrisan
			array[offset].deleteRecord();
			count--;
		}

