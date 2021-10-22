#include <iostream>
#include <queue>
#include "boardDisplay.h"
using namespace std;

void displayBoard(int* board, int n) {

	//delete the matrix
	for (int i = 0; i < n; i++)
		delete board[i];
	delete[] board;
}