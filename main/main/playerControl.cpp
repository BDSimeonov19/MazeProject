#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "playerControl.h"
#include "boardDisplay.h"
#include "boardCreation.h"
using namespace std;

int playerInput() {

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

void controlPlayer(int* path[], int n) {
	int xpos = 0;
	int ypos = 0;

	while (true) {
		system("cls");
		createBoard(path, n, xpos, ypos);

		cout << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				cout << path[i][j];
			cout << endl;
		}
		int input = playerInput();

		//check the validity of the movement by looking at the cell we're trying to get into and seeing how the path got there
		if (input == 0 && xpos != 0 && (path[xpos - 1][ypos] % 5 == 1 || path[xpos][ypos] % 5 == 3))
			xpos--;

		if (input == 1 && ypos != n - 1 && (path[xpos][ypos + 1] % 5 == 2 || path[xpos][ypos] % 5 == 4))
			ypos++;

		if (input == 2 && xpos != n - 1 && (path[xpos + 1][ypos] % 5 == 3 || path[xpos][ypos] % 5 == 1))
			xpos++;

		if (input == 3 && ypos != 0 && (path[xpos][ypos - 1] % 5 == 4 || path[xpos][ypos] % 5 == 2))
			ypos--;

		HANDLE hdlOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hdlOut == INVALID_HANDLE_VALUE)
		{
			cerr << "Encountered an Error: " << GetLastError();
			system("cls");
		}

		if (input == -1) {
			system("cls");
			cout << "Paused\n";

			SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "Create a new maze\n";
			SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

			input = playerInput();

			if (input == -1)
				continue;
			if (input == -2)
				setup();
		}
	}
}