#include <iostream>
#include "boardDisplay.h"
using namespace std;

void displayBoard(int* board[], int n, int playerPosx, int playerPosy) {
	for (int i = 0; i < n; i++)
		cout << " _";
	cout << endl;
	
	for (int i = 0; i < n; i++) {
		cout << "|";
		for (int j = 0; j < n; j++) {
			char player = ' ';
			if (i == playerPosx && j == playerPosy)
				player = '@';
			switch (board[i][j]) {
			case 0:
				cout << underline << player << normal << "|";
				break;
			case 1:
				cout << player << "|";
				break;
			case 2:
				cout << underline << player << normal << " ";
				break;
			default:
				cout << player << " ";
				break;
			}
		}
		cout << endl;
	}
	cout << "x - " << playerPosx << endl;
	cout << "y - " << playerPosy << endl;
}

void createBoard(int* path[], int n, int playerPosx, int playerPosy) {

	//create a dynamic matrix
	int** board = new int* [n];
	for (int i = 0; i < n; i++)
		board[i] = new int[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			board[i][j] = 0;
	}

	//change the _| depending on how the path got there, using the information stored in the cell
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			switch (path[i][j]%5) {
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


	displayBoard(board, n, playerPosx, playerPosy);

	//delete the matrix
	for (int i = 0; i < n; i++)
		delete board[i];
	delete[] board;
}