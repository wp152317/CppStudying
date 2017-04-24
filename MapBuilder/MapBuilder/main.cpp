#include "MapBuilder.h"
#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#define blank "　"
#define block "■"
#define star "★"


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
			case 0:	//noGround
				color(0,4);
				printf(blank);
				break;
			case 1:	//floor
			case 5:	//road
				color(0, 8);
				printf(blank);
				break;
			case 2:	//wall
				color(0, 15);
				printf(blank);
				break;
			case 3:	//door
			case 4:
				color(6, 8);
				printf(block);
				break;
			case 6:	//road-wall
				color(0, 7);
				printf(blank);
				break;
			case 7:	//Player
				color(9, 8);
				printf(star);
				break;
			case 8:	//Monster?
				color(12, 8);
				printf(star);
				break;
			}
		}
	}
	color(0, 0);
	for (int i = 0; i < size; i++) {
		gotoxy(size, i);
		printf(blank);
	}
}

void save(int** map,const int size,unsigned int seed) {
	FILE* fp;
	if ((fp = fopen("Map.mpb", "wt"))==NULL) {
		printf("파일 저장에 실패하였습니다.");
	}
	fprintf(fp, "%d %u\n",size, seed);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fprintf(fp," %2d", map[j][i]);
		}
		fprintf(fp, "\n");
	}
	fflush(fp);
	fclose(fp);
}

int main() {
	int  **map, n;
	unsigned int seed;
	printf("사이즈 입력(%d~%d) >>", MIN_SIZE, MAX_SIZE);
	scanf("%d", &n);
	printf("맵을 저장하시겠습니까?[y/n]\n");
	if (_getch() == 'y') {
		map = buildMap(n, &seed);
	}
	else {
		map = buildMap(n);
	}
	if (map == NULL) {
		printf("size 값이 잘못되었습니다.\n");
		return 0;
	}
	resizeWindow(n);
	drawMap(map, n);
	color(15, 0);
	if(seed!=0)
		save(map,n,seed);
	_getch();
}