#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "playerControl.h"
#include "boardDisplay.h"
#include "boardCreation.h"
#include "mainMenu.h"
using namespace std;

void winScreen() {
	HANDLE hdlOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hdlOut == INVALID_HANDLE_VALUE)
	{
		cerr << "Encountered an Error: " << GetLastError();
		system("cls");
	}

	system("cls");
	cout << "Congratulations!, you solved the maze!\n";
	
	SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Try another maze\n";
	SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	while (true) {
		if (userInput() == -2)
			setup();
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

		HANDLE hdlOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hdlOut == INVALID_HANDLE_VALUE)
		{
			cerr << "Encountered an Error: " << GetLastError();
			system("cls");
		}

		if (xpos == n - 1 && ypos == n - 1)
			winScreen();

		if (input == -1) {
			int choice = 0;
			while (true) {
				system("cls");
				cout << "Paused\n";

				if (choice == 0)
					SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "Create a new maze\n";
				SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

				if (choice == 1)
					SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "Help\n";
				SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

				if (choice == 2)
					SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "Autosolve\n";
				SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

				int input = userInput();
				if (input == 0 && choice != 0)
					choice--;
				else if (input == 2 && choice != 2)
					choice++;

				//select an option
				if (input == -1)
					break;

				if (input == -2) {
					system("cls");
					if (choice == 0)
						setup();
					if (choice == 1)
						helpMenu();
					if (choice == 2);
						//add autosolve and developer mode
				}
			}
		}
	}
}