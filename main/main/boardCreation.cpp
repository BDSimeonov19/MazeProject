#include <iostream>
#include "boardCreation.h"
#include "boardDisplay.h"
using namespace std;


void displaypath(bool* path[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << path[i][j] << " ";
		cout << endl;
	}
}

void createPath(bool* path[], int n) {
	int pos1 = 0, pos2 = 0, counter = 0;
	path[pos1][pos2] = 1;
	while (path[n - 1][n - 1] != 1) {
		counter++;

		//reset if path is impossible
		if ((pos1 == n - 1 || path[pos1 + 1][pos2] != 0) && (pos1 == 0 || path[pos1 - 1][pos2] != 0) && (pos2 == n - 1 || path[pos1][pos2 + 1] != 0) && (pos2 == 0 || path[pos1][pos2 - 1] != 0)) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++)
					path[i][j] = 0;
			}
			pos1 = 0;
			pos2 = 0;
			path[pos1][pos2] = 1;
			counter = 0;
		}


		//randomly generate a path
		int move = rand() % 4;

		switch (move) {
		case 0:
			if (pos1 != 0 && path[pos1 - 1][pos2] != 1) {
				pos1--;
				path[pos1][pos2] = 1;
			}
			break;
		case 1:
			if (pos2 != n - 1 && path[pos1][pos2 + 1] != 1) {
				pos2++;
				path[pos1][pos2] = 1;
			}
			break;
		case 2:
			if (pos1 != n - 1 && path[pos1 + 1][pos2] != 1) {
				pos1++;
				path[pos1][pos2] = 1;
			}
			break;
		case 3:
			if (pos2 != 0 && path[pos1][pos2 - 1] != 1) {
				pos2--;
				path[pos1][pos2] = 1;
			}
			break;
		}
	}
	system("cls");
	displaypath(path, n);
}

void setup()
{
	int n;
	cout << "Input a board size\n";
	cout << "(note: board sizes above ~35 take much longer to create)\n";
	cin >> n;


	//create a dynamic matrix
	bool** path = new bool* [n];
	for (int i = 0; i < n; i++)
		path[i] = new bool[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			path[i][j] = 0;
	}


	createPath(path, n);


	//delete the matrix
	for (int i = 0; i < n; i++)
		delete path[i];
	delete[] path;
}