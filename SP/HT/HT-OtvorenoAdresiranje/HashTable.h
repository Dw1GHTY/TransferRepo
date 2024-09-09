#pragma once
#include"HashObject.h"

template <class T, class R>
class HashTable
{
protected:
	unsigned int length; // velicinatablice
	unsigned int count;  //brojelemenatau tablici
protected:
	unsigned int h(HashObject<T, R> obj) {
		return (f(obj.getKey()) % length);
	}
	// primarnatransformacija
	virtual unsigned int f(int i) { return abs(i); }
	virtual unsigned int f(double d) {
		if (d == 0) return 0;
		else
		{
			int exponent;
			double mantissa = frexp(d, &exponent);
			return (unsigned int)((2 * fabs(mantissa) - 1) * ~0U);
		}
	}
	virtual unsigned int f(char* s)
	{
		unsigned int res = 0;
		unsigned int a = 7;
		for (int i = 0; s[i] != 0; i++)
			res = res << a ^ s[i];
		return res;
	}
	// sekundarnatransformacija
	virtual unsigned int g(unsigned int i)
	{
		return (i + 1) % length;
	}
public:
	unsigned intgetLength() { return length; }
	virtual double getLoadFactor() {
		return (double)count / (double)length;
	}
};

