#include <iostream>
#include <ctime>
#include "boardCreation.h"
#include "playerControl.h"
#include "grand.h"
using namespace std;
GRand rng;

void generatePath(int* path[], int* x, int* y, int n, bool isBranch, int nthBranch) {
	//reset if path is impossible and isn't a branch
	if ((*x == n - 1 || path[*x + 1][*y] != 0) && (*x == 0 || path[*x - 1][*y] != 0) && (*y == n - 1 || path[*x][*y + 1] != 0) && (*y == 0 || path[*x][*y - 1] != 0) && !isBranch) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				path[i][j] = 0;
		}
		*x = 0;
		*y = 0;
	}

	//stop altogether if an error is made
	else if (!((*x == n - 1 || path[*x + 1][*y] != 0) && (*x == 0 || path[*x - 1][*y] != 0) && (*y == n - 1 || path[*x][*y + 1] != 0) && (*y == 0 || path[*x][*y - 1] != 0) && isBranch)) {



		//randomly generate a path
		int move = rng.i(4);


		//store the movement taken to get to the current cell
		switch (move) {
		case 0:
			if (*x != 0 && path[*x - 1][*y] == 0) {
				*x -= 1;
				path[*x][*y] = nthBranch * 5 + 1;
			}
			break;
		case 1:
			if (*y != n - 1 && path[*x][*y + 1] == 0) {
				*y += 1;
				path[*x][*y] = nthBranch * 5 + 2;
			}
			break;
		case 2:
			if (*x != n - 1 && path[*x + 1][*y] == 0) {
				*x += 1;
				path[*x][*y] = nthBranch * 5 + 3;
			}
			break;
		case 3:
			if (*y != 0 && path[*x][*y - 1] == 0) {
				*y -= 1;
				path[*x][*y] = nthBranch * 5 + 4;
			}
			break;
		}
	}
}

void mainPath(int* path[], int n) {
	int x = 0, y = 0;
	int* xptr = &x;
	int* yptr = &y;

	while (path[n - 1][n - 1] == 0)
		generatePath(path, xptr, yptr, n, false, 0);
}

void branchPath(int* path[], int n, int nthBranch) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//decides whether to make a branch
			if (rng.b(0.50) && (path[i][j] == nthBranch * 5 + 1 || path[i][j] == nthBranch * 5 + 2 || path[i][j] == nthBranch * 5 + 3 || path[i][j] == nthBranch * 5 + 4)) {
				int x = i, y = j, len = 0;
				int* xptr = &x;
				int* yptr = &y;
				//expands the branch
				while (rng.b(0.95)) {
					len++;
					generatePath(path, xptr, yptr, n, true, nthBranch + 1);
				}
			}
		}
	}
}

void setup()
{
	int n;
	cout << "Input a board size\n";
	cout << "(note: board sizes above ~35 take much longer to create)\n";
	cin >> n;


	//create a dynamic matrix
	int** path = new int* [n];
	for (int i = 0; i < n; i++)
		path[i] = new int[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			path[i][j] = 0;
	}


	mainPath(path, n);
	//todo fucking branches pls
	for (int i = 0; i < n/5; i++)
		branchPath(path, n, i);
	controlPlayer(path, n);


	//delete the matrix
	for (int i = 0; i < n; i++)
		delete path[i];
	delete[] path;
}