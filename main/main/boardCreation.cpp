#include <iostream>
#include <ctime>
#include <queue>
#include "boardCreation.h"
#include "boardDisplay.h"
#include "grand.h"
using namespace std;
GRand rng;

void generatePath(int* path[], int* x, int* y, int n, bool isBranch) {
	//reset if path is impossible
	if ((*x == n - 1 || path[*x + 1][*y] != 0) && (*x == 0 || path[*x - 1][*y] != 0) && (*y == n - 1 || path[*x][*y + 1] != 0) && (*y == 0 || path[*x][*y - 1] != 0) && !isBranch) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				path[i][j] = 0;
		}
		*x = 0;
		*y = 0;
		path[*x][*y] = 1;
	}


	//randomly generate a path
	int move = rng.i(4);

	switch (move) {
	case 0:
		if (*x != 0 && path[*x - 1][*y] == 0) {
			*x-=1;
			//if (!isBranch)
				path[*x][*y] = 1;
			/*else
				path[*x][*y] = 2;*/
		}
		break;
	case 1:
		if (*y != n - 1 && path[*x][*y + 1] == 0) {
			*y+=1;
			//if (!isBranch)
				path[*x][*y] = 2;
			/*else
				path[*x][*y] = 2;*/
		}
		break;
	case 2:
		if (*x != n - 1 && path[*x + 1][*y] == 0) {
			*x+=1;
			//if (!isBranch)
				path[*x][*y] = 3;
			/*else
				path[*x][*y] = 2;*/
		}
		break;
	case 3:
		if (*y != 0 && path[*x][*y - 1] == 0) {
			*y-=1;
			//if (!isBranch)
				path[*x][*y] = 4;
			/*else
				path[*x][*y] = 2;*/
		}
		break;
	}
}

void mainPath(int* path[], int n) {
	int x = 0, y = 0;
	int* xptr = &x;
	int* yptr = &y;
	path[x][y] = 1;
	
	while (path[n - 1][n - 1] == 0)
		generatePath(path, xptr, yptr, n, false);
}

/*void branchPath(int* path[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//decides whether to make a branch
			if (path[i][j] == 1 && rng.b(0.25)) {
				int x = i, y = j, len = 0;
				int* xptr = &x;
				int* yptr = &y;
				//expands the branch
				while (rng.b(0.95)) {
					len++;
 					generatePath(path, xptr, yptr, n, true);
				}
			}
		}
	}
}*/

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
	//branchPath(path, n);
	createBoard(path, n);


	//delete the matrix
	/*for (int i = 0; i < n; i++)
		delete path[i];
	delete[] path;*/
}