#include <iostream>
#include <queue>
#include "boardDisplay.h"
using namespace std;

void displayBoard(int* board[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			switch (board[i][j]) {
			case 0:
				cout << "_|";
				break;
			case 1:
				cout << " |";
				break;
			case 2:
				cout << "_ ";
				break;
			case 3:
				cout << "  ";
				break;
			}
		}
		cout << endl;
	}
}

void createBoard(int* path[], int n) {

}