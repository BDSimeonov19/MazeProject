#include <iostream>
#include <ctime>
#include "boardCreation.h"
#include "playerControl.h"
#include "grand.h"
using namespace std;
GRand rng;

/// <summary>
/// Randomly generates a path based on the inputs given. Resets the path taken if it gets stuck.
/// </summary>
/// <param name="path">
/// A dynamic matrix which stores the paths on the board and the instructions to get to them
/// </param>
/// <param name="xpos">
/// Current position of the path on the x coordinate
/// </param>
/// <param name="ypos">
/// Current position of the path on the y coordinate
/// </param>
/// <param name="n">
/// The size of the board
/// </param>
/// <param name="isBranch">
/// A value which checks whether the current path is a branch or not
/// </param>
/// <param name="nthBranch">
/// Check what layer of branch the function is making
/// </param>
void generatePath(int* path[], int* xpos, int* ypos, int n, bool isBranch, int nthBranch) {
	//reset if path is impossible and isn't a branch
	if ((*xpos == n - 1 || path[*xpos + 1][*ypos] != 0) && \
		(*xpos == 0 || path[*xpos - 1][*ypos] != 0) && \
		(*ypos == n - 1 || path[*xpos][*ypos + 1] != 0) && \
		(*ypos == 0 || path[*xpos][*ypos - 1] != 0) && \
		!isBranch) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				path[i][j] = 0;
		}
		*xpos = 0;
		*ypos = 0;
	}

	//stop altogether if an error is made
	else if (!((*xpos == n - 1 || path[*xpos + 1][*ypos] != 0) && \
		(*xpos == 0 || path[*xpos - 1][*ypos] != 0) && \
		(*ypos == n - 1 || path[*xpos][*ypos + 1] != 0) && \
		(*ypos == 0 || path[*xpos][*ypos - 1] != 0) && \
		isBranch)) {



		//randomly generate a path
		int move = rng.i(4);


		//store the movement taken to get to the current cell
		switch (move) {
		case 0:
			if (*xpos != 0 && path[*xpos - 1][*ypos] == 0) {
				*xpos -= 1;
				path[*xpos][*ypos] = nthBranch * 5 + 1;
			}
			break;
		case 1:
			if (*ypos != n - 1 && path[*xpos][*ypos + 1] == 0) {
				*ypos += 1;
				path[*xpos][*ypos] = nthBranch * 5 + 2;
			}
			break;
		case 2:
			if (*xpos != n - 1 && path[*xpos + 1][*ypos] == 0) {
				*xpos += 1;
				path[*xpos][*ypos] = nthBranch * 5 + 3;
			}
			break;
		case 3:
			if (*ypos != 0 && path[*xpos][*ypos - 1] == 0) {
				*ypos -= 1;
				path[*xpos][*ypos] = nthBranch * 5 + 4;
			}
			break;
		}
	}
}

/// <summary>
/// Generates the main path
/// </summary>
/// <param name="path">
/// A dynamic matrix which stores the paths on the board and the instructions to get to them
/// </param>
/// <param name="n">
/// The size of the board
/// </param>
void mainPath(int* path[], int n) {
	int xpos = 0, ypos = 0;
	int* xptr = &xpos;
	int* yptr = &ypos;
	//generates a path while the the bottom right cell is not a path
	while (path[n - 1][n - 1] == 0)
		generatePath(path, xptr, yptr, n, false, 0);
}

/// <summary>
/// Generates the branches
/// </summary>
/// <param name="path">
/// A dynamic matrix which stores the paths on the board and the instructions to get to them
/// </param>
/// <param name="n">
/// The size of the board
/// </param>
/// <param name="nthBranch">
/// The layer of branch the function will act upon
/// </param>
/// <param name="branchBeginChance">
/// Chance of starting a branch
/// </param>
/// <param name="branchEndChance">
/// Chance of ending a branch
/// </param>
void branchPath(int* path[], int n, int nthBranch, float branchBeginChance, float branchEndChance) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//decides whether to make a branch
			if (rng.b(branchBeginChance) && (path[i][j] == nthBranch * 5 + 1 || path[i][j] == nthBranch * 5 + 2 || path[i][j] == nthBranch * 5 + 3 || path[i][j] == nthBranch * 5 + 4)) {
				int xpos = i, ypos = j, len = 0;
				int* xptr = &xpos;
				int* yptr = &ypos;
				//expands the branch
				while (rng.b(branchEndChance)) {
					len++;
					generatePath(path, xptr, yptr, n, true, nthBranch + 1);
				}
			}
		}
	}
}

/// <summary>
/// A setup function before calling in the board creation. Makes a dynamic matrix and variables that will be used in the future
/// </summary>
/// <param name="branchBeginChance">
/// Chance of starting a branch
/// </param>
/// <param name="branchEndChance">
/// Chance of ending a branch
/// </param>
void setup(float branchBeginChance, float branchEndChance) {
	int n;
	system("cls");
	cout << "Input a board size\n";
	cout << "(note: board sizes above ~50 take much longer to create)\n";
	cin >> n;


	//create a dynamic matrix
	int** path = new int* [n];
	for (int i = 0; i < n; i++)
		path[i] = new int[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			path[i][j] = 0;
	}

	//creates a main path
	mainPath(path, n);
	for (int i = 0; i < n / 2; i++)
		//creates an arbitrary number of branches
		branchPath(path, n, i, branchBeginChance, branchEndChance);
	//calls player control functions
	controlPlayer(path, n);


	//delete the matrix
	for (int i = 0; i < n; i++)
		delete path[i];
	delete[] path;
}