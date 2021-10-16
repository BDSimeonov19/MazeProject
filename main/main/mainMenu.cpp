#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "mainMenu.h"
#include "boardCreation.h"
using namespace std;

int userInput() {

    //check user input
    switch ((_getch())) {
    case 'w':
        return 0;
        break;
    case 's':
        return 1;
        break;
    case '\r':
        return 2;
        break;
    default:
        return -1;
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
    cout << "|, _ and + characters are walls and thus\n";
    cout << "cannot be passed through. Your character\n";
    cout << "is marked with an @ symbol. You move with\n";
    cout << "the WASD keys.";

    SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "\nGo back\n";
    SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    while(true) {
        if (userInput() == 2) {
            system("cls");
            mainMenu();
        }
    }
    
}

void mainMenu() {
    bool firstPicked = true;
    int* choice = new int;
    *choice = 0;
    
    HANDLE hdlOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hdlOut == INVALID_HANDLE_VALUE)
    {
        cerr << "Encountered an Error: " << GetLastError();
        system("cls");
    }

    while (true) {
        cout << "Maze Puzzle!\n";
        cout << "(note: use W, S and Enter to select)\n";
        if (*choice == 0) {
            SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            firstPicked = true;
        }
        cout << "Start\n";
        SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        if (*choice == 1) {
            SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            firstPicked = false;
        }
        cout << "Help\n";
        SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        
        int pick = userInput();
        if (pick > -1)
            *choice = pick;

        //select an option
        if (*choice == 2) {
            system("cls");
            if (firstPicked)
                setup();
            if (!firstPicked)
                helpMenu();
            break;
        }
        system("cls");
    }

    delete choice;
}
