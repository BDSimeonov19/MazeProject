#include "boardCreation.h"
#include <iostream>
using namespace std;

void displayBoard(bool* ptr[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << ptr[i][j] << " ";
		cout << endl;
	}
}

void createPath(bool* ptr[], int n) {
	int pos1 = 0, pos2 = 0, counter = 0;
	ptr[pos1][pos2] = 1;
	while (ptr[n - 1][n - 1] != 1) {
		counter++;

		//reset if path is impossible
		if (counter > n * n * n) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++)
					ptr[i][j] = 0;
			}
			pos1 = 0;
			pos2 = 0;
			ptr[pos1][pos2] = 1;
			counter = 0;
		}


		//randomly generate a path
		int move = rand() % 4;

		switch (move) {
		case 0:
			if (pos1 != 0 && ptr[pos1 - 1][pos2] != 1) {
				pos1--;
				ptr[pos1][pos2] = 1;
			}
			break;
		case 1:
			if (pos2 != n - 1 && ptr[pos1][pos2 + 1] != 1) {
				pos2++;
				ptr[pos1][pos2] = 1;
			}
			break;
		case 2:
			if (pos1 != n - 1 && ptr[pos1 + 1][pos2] != 1) {
				pos1++;
				ptr[pos1][pos2] = 1;
			}
			break;
		case 3:
			if (pos2 != 0 && ptr[pos1][pos2 - 1] != 1) {
				pos2--;
				ptr[pos1][pos2] = 1;
			}
			break;
		}
	}
}

void createWalls(int* ptr[], int n) {

}

void start()
{
	int n;
	cin >> n;

	//create dynamic matrices
	bool** path = new bool* [n];
	for (int i = 0; i < n; i++)
		path[i] = new bool[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			path[i][j] = 0;
	}

	char** board = new char* [n];
	for (int i = 0; i < n; i++)
		board[i] = new char[n];


	createPath(path, n);
	displayBoard(path, n);



	/*createWalls(board, n);*/

	//delete both matrices
	for (int i = 0; i < n; i++)
		delete path[i];
	delete[] path;

	for (int i = 0; i < n; i++)
		delete board[i];
	delete[] board;
}