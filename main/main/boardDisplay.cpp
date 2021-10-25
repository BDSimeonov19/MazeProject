#include <iostream>
#include "boardDisplay.h"
using namespace std;

void displayBoard(int* board[], int n, int xpos, int ypos) {
	for (int i = 0; i < n; i++)
		cout << " _";
	cout << endl;
	
	for (int i = 0; i < n; i++) {
		cout << "|";
		for (int j = 0; j < n; j++) {
			char player = ' ';
			if (i == xpos && j == ypos)
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
		if (i == n - 1)
			cout << "<- end of maze";
		cout << endl;
	}


	/*cout << "x - " << xpos << endl;
	cout << "y - " << ypos << endl;*/
}

void createBoard(int* path[], int n, int xpos, int ypos) {

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


	displayBoard(board, n, xpos, ypos);

	//delete the matrix
	for (int i = 0; i < n; i++)
		delete board[i];
	delete[] board;
}