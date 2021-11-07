#include <iostream>
#include "boardDisplay.h"
using namespace std;

/// <summary>
/// Displays the current board state using the parameters given. Adds the player to that board and updates only when there's a change in the board state
/// </summary>
/// <param name="board">
/// A dynamic matrix which stores the current board state
/// </param>
/// <param name="n">
/// The size of the board
/// </param>
/// <param name="xpos">
/// Current position of the player on the x coordinate
/// </param>
/// <param name="ypos">
/// Current position of the player on the y coordinate
/// </param>
void displayBoard(int* board[], int n, int xpos, int ypos) {
	//display the top wall
	for (int i = 0; i < n; i++)
		cout << " _";
	cout << endl;
	
	//for each cell, check what combination of left and bottom wall should be displayed and add the character if necessary
	for (int i = 0; i < n; i++) {
		cout << "|";
		for (int j = 0; j < n; j++) {
			char player = ' ';
			//if the cell matches the player position, display the player
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
			cout << "<- goal";
		cout << endl;
	}
}

/// <summary>
/// Creates a board which intern is displayed and changed depending on the current player position
/// </summary>
/// <param name="path">
/// A dynamic matrix which stores the paths on the board and the instructions to get to them
/// </param>
/// <param name="n">
/// The size of the board
/// </param>
/// <param name="xpos">
/// Current position of the player on the x coordinate
/// </param>
/// <param name="ypos">
/// Current position of the player on the y coordinate
/// </param>
void createBoard(int* path[], int n, int xpos, int ypos) {

	//create a dynamic matrix
	int** board = new int* [n];
	for (int i = 0; i < n; i++)
		board[i] = new int[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			board[i][j] = 0;
	}

	//change the corner wall depending on how the path got there, using the information stored in the cell
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