#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "mainMenu.h"
#include "boardCreation.h"
#include "buttonInputs.h"
using namespace std;

int userInput() {
	//take user input
	int input = _getch();

	if (input == upInput)
		return 0;
	else if (input == leftInput)
		return 1;
	else if (input == downInput)
		return 2;
	else if (input == rightInput)
		return 3;
	else if (input == 27)
		return -1;
	else if (input == '\r')
		return -2;
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

void buttonRemap() {
	int choice = 0;

	HANDLE hdlOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hdlOut == INVALID_HANDLE_VALUE)
	{
		cerr << "Encountered an Error: " << GetLastError();
		system("cls");
	}

	while (true) {
		cout << "-----------------\n";
		cout << "|               |\n";
		cout << "| Remap buttons |\n";
		cout << "|               |\n";
		cout << "-----------------\n";
		cout << "(note: use W, S and Enter to select)\n";

		//option 1
		if (choice == 0)
			SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Up - " << upInput << endl;
		SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		//option 2
		if (choice == 1)
			SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Left - " << leftInput << endl;
		SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		//option 3
		if (choice == 2)
			SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Down - " << downInput << endl;
		SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		//option 4
		if (choice == 3)
			SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Right - " << rightInput << endl;
		SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		//take user input
		int input = userInput();
		if (input == 0 && choice != 0)
			choice--;
		else if (input == 2 && choice != 5)
			choice++;

		//select an option
		if (input == -2) {
			system("cls");
			switch (choice) {
			case 0:
				upInput = _getch();
				break;
			case 1:
				leftInput = _getch();
				break;
			case 2:
				downInput = _getch();
				break;
			case 3:
				rightInput = _getch();
				break;
			}
		}
		system("cls");
		
		if (input == -1)
			break;
	}
}

void settingsMenu() {
	int choice = 0;

	HANDLE hdlOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hdlOut == INVALID_HANDLE_VALUE)
	{
		cerr << "Encountered an Error: " << GetLastError();
		system("cls");
	}

	while (true) {
		cout << "-----------------\n";
		cout << "|               |\n";
		cout << "|    Settings   |\n";
		cout << "|               |\n";
		cout << "-----------------\n";
		cout << "(note: use W, S and Enter to select)\n";

		//option 1
		if (choice == 0)
			SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "  Remap buttons\n";
		SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		//option 2
		if (choice == 1)
			SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "  Developer mode\n";
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
				buttonRemap();
			if (choice == 1);

		}
		system("cls");
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
		cout << "-----------------\n";
		cout << "|               |\n";
		cout << "|  Maze Puzzle! |\n";
		cout << "|               |\n";
		cout << "-----------------\n";
		cout << "(note: use W, S and Enter to select)\n";

		//option 1
		if (choice == 0)
			SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "      Start\n";
		SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		//option 2
		if (choice == 1)
			SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "      Help\n";
		SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

		//option 3
		if (choice == 2)
			SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "    Settings\n";
		SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);


		//take user input
		int input = userInput();
		if (input == 0 && choice != 0)
			choice--;
		else if (input == 2 && choice != 2)
			choice++;

		//select an option
		if (input == -2) {
			system("cls");
			if (choice == 0)
				setup();
			if (choice == 1)
				helpMenu();
			if (choice == 2)
				settingsMenu();
		}
		system("cls");
	}
}
