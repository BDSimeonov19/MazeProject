#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "mainMenu.h"
#include "boardCreation.h"
using namespace std;

int userInput() {
	//take user input
	switch ((_getch())) {
	case 'w':
		return 0;
		break;
	case 'd':
		return 1;
		break;
	case 's':
		return 2;
		break;
	case 'a':
		return 3;
		break;
	case 27:
		return -1;
		break;
	case '\r':
		return -2;
		break;
	}
}



void helpMenu() {
	HANDLE hdlOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hdlOut == INVALID_HANDLE_VALUE)
	{
		cerr << "Encountered an Error: " << GetLastError();
		system("cls");
	}

	cout << "A maze is a puzzle where the player is\n";
	cout << "positioned in one corner of a board and\n";
	cout << "is tasked to cross to the opposite corner.\n";
	cout << "| and _ characters are walls and thus\n";
	cout << "cannot be passed through. Your character\n";
	cout << "is marked with an @ symbol. You move with\n";
	cout << "the WASD keys.\n";
	cout << "Press escape to open the pause menu.";

	SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "\nGo back\n";
	SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	while (true) {
		if (userInput() == -2) {
			system("cls");
			break;
		}
	}

}

void mainMenu() {
	int choice = 0;

	HANDLE hdlOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hdlOut == INVALID_HANDLE_VALUE)
	{
		cerr << "Encountered an Error: " << GetLastError();
		system("cls");
	}

	while (true) {
		cout << "Maze Puzzle!\n";
		cout << "(note: use W, S and Enter to select)\n";
		if (choice == 0)
			SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Start\n";
		SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		if (choice == 1)
			SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Help\n";
		SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		//take user input
		int input = userInput();
		if (input == 0 && choice != 0)
			choice--;
		else if (input == 2 && choice != 1)
			choice++;

		//select an option
		if (input == -2) {
			system("cls");
			if (choice == 0)
				setup();
			if (choice == 1)
				helpMenu();
		}
		system("cls");
	}
}
