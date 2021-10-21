#include <iostream>
#include <queue>
#include "boardDisplay.h"
using namespace std;

void displayBoard(int* board[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			switch (board[i][j]) {
			case 0:
				cout << "_|";
				break;
			case 1:
				cout << " |";
				break;
			case 2:
				cout << "_ ";
				break;
			case 3:
				cout << "  ";
				break;
			}
		}
		cout << endl;
	}
}

void createBoard(int* path[], int n) {

	//create a dynamic matrix
	int** board = new int* [n];
	for (int i = 0; i < n; i++)
		board[i] = new int[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			board[i][j] = 0;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			switch (path[i][j]) {
			case 1:
				board[i][j] += 1;
				break;
			case 2:
				board[i][j - 1] += 2;
				break;
			case 3:
				board[i - 1][j] += 1;
				break;
			case 4:
				board[i][j] += 2;
				break;
			}
		}
	}

	displayBoard(board, n);

	//delete the matrix
	for (int i = 0; i < n; i++)
		delete path[i];
	delete[] path;
}