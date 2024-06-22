#include "Stack.h"
#include <iostream>
#include <math.h>
using namespace std;
#include <string.h>
void CharPostfix(char* postfix);
void main()
{
	char* postfix = "2 3 + 10 * 5 /";
	CharPostfix(postfix);
}
void CharPostfix(char* postfix)
{
	Stack* s = new Stack(64);
	int i = 0;
	while (i < strlen(postfix))
	{
		if (postfix[i] == '-')
		{
			int first = s->pop();
			int second = s->pop();
			int rez = first - second;
			s->push(rez);
		}
		else if (postfix[i] == '+')
		{
			int first = s->pop();
			int second = s->pop();
			int rez = first + second;
			s->push(rez);
		}
		else if (postfix[i] == '/')
		{
			int first = s->pop();
			int second = s->pop();
			int rez = second / first;
			s->push(rez);
		}
		else if (postfix[i] == '*')
		{
			int first = s->pop();
			int second = s->pop();
			int rez = first * second;
			s->push(rez);
		}
		else if (postfix[i] == ' ')
		{

		}
		else
		{
			int el = 0;
			if (postfix[i + 1] != ' ' )
			{
				int j = 1;				
				while (postfix[i + 1] != ' ' && postfix[i + 1] != '/0')
				{
					i++;//7
					j++;//2
				}
				while (postfix[i]!=' ' && i!='/0' && j>0)
				{
					el = el +(postfix[i]-'0') * pow(10, j%2);
					j--;
					i--;
				}
				while (postfix[i+1] != ' ')
				{
					i++;
				}
				s->push(el);
			}
			else
			{
				el = postfix[i] - '0';
				s->push(el);
			}
		}
		i++;
	}
	std::cout << "rezultat je:" << (int)s->pop() << std::endl;
}