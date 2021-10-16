#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "mainMenu.h"
#include "boardCreation.h"
using namespace std;

int menuChoice(int choice) {

    //check user input
    switch ((_getch())) {
    case 'w':
        if (choice != 0)
            choice = 0;
        break;
    case 's':
        if (choice != 1)
            choice = 1;
        break;
    case '\r':
        return 2;
        break;
    default:
        break;
    }
    return choice;
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
        cout << "(note: use W and S to choose an option)\n";
        if (choice == 0)
            SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "Start\n";
        SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        if (choice == 1)
            SetConsoleTextAttribute(hdlOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "Help\n";
        SetConsoleTextAttribute(hdlOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

        choice = menuChoice(choice);

        if (menuChoice(choice) == 2) {
            system("cls");
            if (choice == 0)
                start();
            if (choice == 1)
                //#todo help menu
                int a = 0;
            break;
        }
        system("cls");
    }

}