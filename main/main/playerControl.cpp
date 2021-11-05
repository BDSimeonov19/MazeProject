#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <iterator>
#include "playerControl.h"
#include "mazeSettings.h"
#include "boardDisplay.h"
#include "boardCreation.h"
#include "mainMenu.h"
using namespace std;

void winScreen() {
	system("cls");
	cout << "Congratulations!, you solved the maze!\n";

	//option
	optionsDisplay("Try another maze", true);

	while (true) {
		if (userInput() == -2)
			setup(branchBeginChance, branchEndChance);
	}
}

void devMenu(float* beginChance, float* endChance) {
	int choice = 0;

	while (true) {
		cout << "-----------------\n";
		cout << "|               |\n";
		cout << "|    Dev menu   |\n";
		cout << "|               |\n";
		cout << "-----------------\n";
		cout << "(note: input values between 0 and 1)\n";

		//options
		optionsDisplay("Chance of making a branch", choice == 0, ' ', *beginChance);
		optionsDisplay("Chance of ending a branch", choice == 1, ' ', *endChance);

		//take user input
		int input = userInput();
		if (input == 0 && choice != 0)
			choice--;
		else if (input == 2 && choice != 1)
			choice++;

		//select an option
		float temp;
		if (input == -2) {
			system("cls");
			cin >> temp;
			if (temp < 0 || temp > 1)
				cout << "You must enter a value between 0 and 1\n";
			else {
				switch (choice) {
				case 0:
					*beginChance = temp;
					break;
				case 1:
					*endChance = temp;
					break;
				}
			}
		}
		system("cls");

		if (input == -1)
			break;
	}
}

void pauseMenu(int choice) {
	HANDLE hdlOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hdlOut == INVALID_HANDLE_VALUE)
	{
		cerr << "Encountered an Error: " << GetLastError();
		system("cls");
	}

	system("cls");
	cout << "-----------------\n";
	cout << "|               |\n";
	cout << "|    Paused     |\n";
	cout << "|               |\n";
	cout << "-----------------\n";

	optionsDisplay(" Create a new maze", choice == 0);
	optionsDisplay("      Help", choice == 1);
	optionsDisplay("    Autosolve", choice == 2);
	optionsDisplay(" Developer options", choice == 3);
}


//autosolver
void autoSolve(int* xpos, int* ypos, int* path[], int n) {
	bool mainPath = false;
	while (*xpos != n - 1 || *ypos != n - 1) {
		system("cls");
		createBoard(path, n, *xpos, *ypos);
		//follos a branch back to the main path
		if (!mainPath) {
			switch (path[*xpos][*ypos] % 5) {
			case 1:
				*xpos+=1;
				break;
			case 2:
				*ypos-= 1;
				break;
			case 3:
				*xpos-= 1;
				break;
			case 4:
				*ypos+= 1;
				break;
			}

			if (path[*xpos][*ypos] < 5)
				mainPath = true;
		}
		else
			break;
	}

	//reverses the instructions of the main path
	int i = n-1, j = n-1;
	vector<int> instructions;

	while (!(*xpos == i && *ypos == j)) {
		instructions.push_back(path[i][j]);

		switch (path[i][j] % 5) {
		case 1:
			i++;
			break;
		case 2:
			j--;
			break;
		case 3:
			i--;
			break;
		case 4:
			j++;
			break;
		}
	}

	//follows the instructions to get to the end
	while (!(*xpos == n-1 && *ypos == n-1)) {
		switch (instructions.back() % 5) {
		case 1:
			*xpos-= 1;
			break;
		case 2:
			*ypos+= 1;
			break;
		case 3:
			*xpos+= 1;
			break;
		case 4:
			*ypos-= 1;
			break;
		}

		instructions.pop_back();

		system("cls");
		createBoard(path, n, *xpos, *ypos);
	}

}

void controlPlayer(int* path[], int n) {
	int xpos = 0;
	int ypos = 0;

	while (true) {
		system("cls");
		createBoard(path, n, xpos, ypos);

		int input = userInput();

		//check the validity of the movement by looking at the cell we're trying to get into and seeing how the path got there
		if (input == 0 && xpos != 0 && (path[xpos - 1][ypos] % 5 == 1 || path[xpos][ypos] % 5 == 3))
			xpos--;

		else if (input == 1 && ypos != n - 1 && (path[xpos][ypos + 1] % 5 == 2 || path[xpos][ypos] % 5 == 4))
			ypos++;

		else if (input == 2 && xpos != n - 1 && (path[xpos + 1][ypos] % 5 == 3 || path[xpos][ypos] % 5 == 1))
			xpos++;

		else if (input == 3 && ypos != 0 && (path[xpos][ypos - 1] % 5 == 4 || path[xpos][ypos] % 5 == 2))
			ypos--;

		if (input == -1) {
			int choice = 0;
			while (true) {

				pauseMenu(choice);

				//check for user input
				int input = userInput();
				if (input == 0 && choice != 0)
					choice--;
				else if (input == 2 && choice != 3)
					choice++;

				//select an option
				if (input == -1)
					break;

				if (input == -2) {
					system("cls");
					if (choice == 0)
						setup(branchBeginChance, branchEndChance);
					if (choice == 1)
						helpMenu();
					if (choice == 2) {
						autoSolve(&xpos, &ypos, path, n);
						break;
					}
					if (choice == 3)
						devMenu(&branchBeginChance, &branchEndChance);
				}
			}
		}

		//win screen check
		if (xpos == n - 1 && ypos == n - 1)
			winScreen();
	}
}