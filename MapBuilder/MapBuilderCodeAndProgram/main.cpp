#include "MapBuilder.h"
#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <string.h>
#define blank "　"
#define block "■"

void gotoxy(short x, short y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 2*x,y });
}

void color(short fc, short bgc) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fc + bgc * 16);
}

void resizeWindow(int size) {
	char str[100];
	sprintf(str, "mode con: lines=%d cols=%d", size + 1, size * 2 + 3);
	system(str);
}

void drawMap(int** map,const int size) {
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			gotoxy(i, j);
			switch (map[i][j]) {
			case 0:
				color(0,4);
				printf(blank);
				break;
			case 1:
			case 5:
				color(0, 7);
				printf(blank);
				break;
			case 2:
				color(0, 15);
				printf(blank);
				break;
			case 3:
				color(9,7);
				printf(block);
				break;
			case 4:
				color(12, 7);
				printf(block);
				break;
			}
		}
	}
}

int main() {
	int  **map,n;
	scanf("%d", &n);
	map=buildMap(n);
	if (map == NULL) {
		printf("size 값이 잘못되었습니다.\n");
		return 0;
	}
	resizeWindow(n);
	drawMap(map, n);
}