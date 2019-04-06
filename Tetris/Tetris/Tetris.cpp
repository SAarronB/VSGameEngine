// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
//#include "engineController.cpp"
//#include "enginePanel.cpp"
//#include "engineFrame.cpp"
#include <iostream>
using namespace std;

#include "pch.h"
#include <Windows.h>

wstring tetromino[7];

int mapWidth = 12;
int mapHeight = 18;
unsigned char *pMap = nullptr;

int screenWidth = 80;	//Console size COLUMNS
int screenHeight = 63; //Console size ROWS

int Rotate(int x, int y, int r) {

	switch (r % 4) {
	case 0: return y * 4 + x;			//0 Degree Rotation
	case 1: return 12 + y - (x * 4);	// 90 Degree Rotation
	case 2: return 15 - (y * 4) - x;	// 180 Degree Rotation
	case 3: return 3 - y + (x * 4);		// 270 Degree Rotation
	}
	return 0;
}

bool CheckFit(int Tetromino, int Rotaion, int xPos, int yPos) {

	for (int a = 0; a < 4; a++) {
		for (int b = 0; b < 4; b++) {
			//Get index of the piece
			int posIndex = Rotate(a, b, Rotaion);

			//Get index into field
			int fiIndex = (yPos + b) * mapWidth + (xPos + a);

			if (xPos + a >= 0 && xPos + a < mapHeight) {
				if (yPos + b >= 0 && yPos + b < mapHeight) {
					if (tetromino[Tetromino][posIndex] == L'X' && pMap[fiIndex] != 0) {
						return false;//fails on first Hit
					}
				}
			}
		}
	}

	return true;
}

int main() {

	//Create assets (MOVE THIS TO MODUEL FOLDER AND NAME IT COMPONENTS)
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	tetromino[2].append(L"....");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"..X.");

	tetromino[3].append(L".X..");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"..X.");
	tetromino[3].append(L"....");

	tetromino[4].append(L"....");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L".X..");
	tetromino[4].append(L".X..");

	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"....");

	tetromino[6].append(L"..X.");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L"..X.");
	tetromino[6].append(L"....");

	tetromino[7].append(L".X..");
	tetromino[7].append(L".XX.");
	tetromino[7].append(L".X..");
	tetromino[7].append(L"....");

	// MOVE TO MODUEL AND NAME IT MAP

	pMap = new unsigned char[mapWidth * mapHeight];	//Initializes an array and creates a buffer for map.

	//Boundry of map.
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			//					   if x is V or V is 11 ----------or V is 17-----------then set boarder to 9 if not then set to 0
			pMap[y * mapWidth + x] = (x == 0 || x == mapWidth - 1 || y == mapHeight - 1) ? 9 : 0;
		}
	}

	// MOVE TO VIEW AND NAME IT CONSOLE
	wchar_t *screen = new wchar_t[screenWidth * screenHeight];
	for (int i = 0; i < screenWidth * screenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwByTesWriteen = 0;


	// MOVE THIS TO MODUEL AND NAME IT GAME LOGIC
	//Game loops (Game Sequencing)
	bool gameOver = false;

	while (!gameOver) {

		//Game Timeing =====================================

		//Input ============================================

		//Game Logic =======================================

		bool gameOver = false;

		int currentPiece = 1;
		int currentRotation = 0;
		int currentX = mapWidth / 2;
		int currentY = 0;

		while (!gameOver){}

		//Render OutPut=====================================

		//Draw Field========================================
		for (int x = 0; x < mapWidth; x++) {
			for (int y = 0; y < mapHeight; y++)
				//			Setting out put depending on V depending on the value of V
				screen[(y + 2) * screenWidth + (x + 2)] = L" ABCDEFG=#"[pMap[y * mapWidth + x]];
		}

		//Draw Current Piece===============================
		//Iterats over all the cells in tetromino
		for (int a = 0; a < mapWidth; a++) {
			for (int b = 0; b < 4; b++) {
				//gets piece______________ finds index that is rotated__if X__________________________ Draw to screen______________________________________________A
				if (tetromino[currentPiece][Rotate(a, b, currentRotation)] == L'X') screen[(currentY + b + 2) * screenWidth + (currentX + a + 2)] = currentPiece + 65;
			}
		}

		//Display Frame (Screen Buffer Array)==============
		WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, { 0,0 }, &dwByTesWriteen);
	}


	return 0;
}
