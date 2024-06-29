#include "Board.h"
#include <iostream>

using namespace std;

Board::Board() 
{
	for (int i = 0; i < 3; i++) 
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j] = 0;
		}
	}
}

void Board::PrintBoard() 
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << "\t" << board[i][j];
		}
		cout << "\n"
	}
}