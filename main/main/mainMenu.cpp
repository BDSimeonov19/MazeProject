#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include "mainMenu.h"
#include "boardCreation.h"
#include "buttonInputs.h"
using namespace std;

int userInput() {
	//take user input
	int input = _getch();

	if (input == upInput)
		return 0;
	else if (input == rightInput)
		return 1;
	else if (input == downInput)
		return 2;
	else if (input == leftInput)
		return 3;
	else if (input == 27)
		return -1;
	else if (input == '\r')
		return -2;
}

void optionsDisplay(string str, bool chosen, char ch) {
	HANDLE hdlOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hdlOut == INVALID_HANDLE_VALUE)
	{
		cerr << "Encountered an Error: " << GetLastError();
		system("cls");
	}
	if (chosen)
		SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << str << ch << endl;
	SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void helpMenu() {


	cout << "A maze is a puzzle where the player is\n";
	cout << "positioned in one corner of a board and\n";
	cout << "is tasked to cross to the opposite corner.\n";
	cout << "| and _ characters are walls and thus\n";
	cout << "cannot be passed through. Your character\n";
	cout << "is marked with an @ symbol. You move with\n";
	cout << "the WASD keys.\n";
	cout << "Press escape to open the pause menu.\n";


	while (true) {
		if (userInput() == -1) {
			system("cls");
			break;
		}
	}

}

void buttonRemap() {
	int choice = 0;


	while (true) {
		cout << "-----------------\n";
		cout << "|               |\n";
		cout << "| Remap buttons |\n";
		cout << "|               |\n";
		cout << "-----------------\n";
		cout << "(note: use W, S and Enter to select)\n";

		//options
		optionsDisplay("Up - ", choice == 0, upInput);
		optionsDisplay("Left - ", choice == 1, leftInput);
		optionsDisplay("Down - ", choice == 2, downInput);
		optionsDisplay("Right - ", choice == 3, rightInput);

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

	while (true) {
		cout << "-----------------\n";
		cout << "|               |\n";
		cout << "|    Settings   |\n";
		cout << "|               |\n";
		cout << "-----------------\n";
		cout << "(note: use W, S and Enter to select)\n";

		//options
		optionsDisplay("  Remap buttons", choice == 0);
		optionsDisplay("  Developer mode", choice == 1);

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

		if (input == -1)
			break;
	}
}

void mainMenu() {
	int choice = 0;

	while (true) {
		cout << "-----------------\n";
		cout << "|               |\n";
		cout << "|  Maze Puzzle! |\n";
		cout << "|               |\n";
		cout << "-----------------\n";
		cout << "(note: use W, S and Enter to select)\n";

		//options
		optionsDisplay("      Start", choice == 0);
		optionsDisplay("      Help", choice == 1);
		optionsDisplay("    Settings", choice == 2);

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
