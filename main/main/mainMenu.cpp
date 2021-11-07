#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include "mainMenu.h"
#include "boardCreation.h"
#include "inputSettings.h"
using namespace std;

/// <summary>
/// Takes the user input and returns an int between 3 and -3
/// </summary>
/// <returns>
/// A value that stands for the user input, used in other functions
/// </returns>
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
	else
		//return -3 when there's a redundant input
		return -3;
}

/// <summary>
/// Displays the options for the menus and highlits the chosen ones
/// </summary>
/// <param name="str">
/// The string to be displayed
/// </param>
/// <param name="chosen">
/// A boolean value of whether to highlit the text
/// </param>
/// <param name="ch">
/// An extra character that's added to the string
/// </param>
/// <param name="var">
/// A variable that's displayed if inputed
/// </param>
void optionsDisplay(string str, bool chosen, char ch, float var) {
	//error handler
	HANDLE hdlOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hdlOut == INVALID_HANDLE_VALUE)
	{
		cerr << "Encountered an Error: " << GetLastError();
		system("cls");
	}
	//if the text has been chosen, highlit it
	if (chosen)
		SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << str << ch;
	if (var >= 0)
		//if there's a variable to be displayed, display it
		cout << var;
	cout << endl;
	SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

/// <summary>
/// A menu with a description of how to play and what to do
/// </summary>
void helpMenu() {


	cout << "A maze is a puzzle where the player is\n";
	cout << "positioned in one corner of a board and\n";
	cout << "is tasked to cross to the opposite corner.\n";
	cout << "| and _ characters are walls and thus\n";
	cout << "cannot be passed through. Your character\n";
	cout << "is marked with an @ symbol. You move with\n";
	cout << "the WASD keys.\n";
	cout << "Press escape to open the pause menu.\n";

	//take user input to return to main menu
	while (true) {
		if (userInput() == -1) {
			system("cls");
			break;
		}
	}
}

/// <summary>
/// A menu in which you can remap your inputs across the whole game
/// </summary>
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
		optionsDisplay("Up - ", choice == 0, upInput);
		optionsDisplay("Left - ", choice == 1, leftInput);
		optionsDisplay("Down - ", choice == 2, downInput);
		optionsDisplay("Right - ", choice == 3, rightInput);

		//take user input
		int input = userInput();
		if (input == 0 && choice != 0)
			choice--;
		else if (input == 2 && choice != 3)
			choice++;

		//select an option
		if (input == -2) {
			switch (choice) {
				system("cls");
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

/// <summary>
/// The main menu which holds every other menu and the maze itself
/// </summary>
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
				setup(0.5,0.95);
			if (choice == 1)
				helpMenu();
			if (choice == 2)
				settingsMenu();
		}
		system("cls");
	}
}
