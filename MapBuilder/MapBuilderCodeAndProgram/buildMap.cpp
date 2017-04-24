#include "MapBuilder.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

typedef struct Rectangle {
	int left, top, bottom, right;
}rect;

typedef struct Door {
	int xPos, yPos;
	int linkedRoomNum;
	int linkedRoomDoorNum;
}door;

typedef struct Room{
	rect in;
	int doorNum;
	door* doors;
}room;


void intialize(int ***map, const int size) {
	*map= (int**)malloc(sizeof(int*)*size);
	for (int i = 0; i < size; i++) {
		(*map)[i] = (int*)malloc(sizeof(int)*size);
		for (int j = 0; j < size; j++) {
			(*map)[i][j] = 0;
		}
	}
}

bool isOverlapRoom(const room desc,const room src) {
	if(desc.in.top-1>src.in.bottom)
		return false;
	if (desc.in.bottom+1 < src.in.top)
		return false;
	if (desc.in.left-1 > src.in.right)
		return false;
	if (desc.in.right+1 < src.in.left)
		return false;
	return true;
}

void initializeRoom(room* src,const int size) {
	src->in.top=rand() % (size - 7);
	src->in.left = rand() % (size - 7);
	src->in.bottom = src->in.top + 5 + rand() % 3;
	src->in.right = src->in.left + 5 + rand() % 3;
}

int setRoomPos(int ***map, const int size,room* rooms,const int roomNum) {
	//getRoom randomly not connected
	int cnt = 0;
	for (int i = 0; i < roomNum; i++) {
		initializeRoom(&rooms[i], size);
		for (int j = 0; j < i || 0 *
			printf("%d Room's ", i)*
			printf("Rect : (%d,%d),(%d,%d)\n", rooms[i].in.left, rooms[i].in.top, rooms[i].in.right, rooms[i].in.bottom);
			j++) {
			if (isOverlapRoom(rooms[j], rooms[i])) {
				i--;
				break;
			}
		}
		cnt++;
		if (cnt == 1000000) {
			return 1;
		}
	}
	//set Wall and set InRoom
	for (int i = 0; i < roomNum; i++) {
		(*map)[rooms[i].in.left][rooms[i].in.top] = 2;
		(*map)[rooms[i].in.left][rooms[i].in.bottom] = 2;
		(*map)[rooms[i].in.right][rooms[i].in.top] = 2;
		(*map)[rooms[i].in.right][rooms[i].in.bottom] = 2;
		for (int x = rooms[i].in.left + 1; x < rooms[i].in.right; x++) {
			for (int y = rooms[i].in.top + 1; y < rooms[i].in.bottom; y++) {
				(*map)[x][y] = 1;
			}
			(*map)[x][rooms[i].in.top] = 2;
			(*map)[x][rooms[i].in.bottom] = 2;
		}
		for (int y = rooms[i].in.top + 1; y < rooms[i].in.bottom; y++) {
			(*map)[rooms[i].in.left][y] = 2;
			(*map)[rooms[i].in.right][y] = 2;
		}
	}
	return 0;
}

int initializeDoor(room* rooms,const int roomNum,int size ){
	int cnt = 0;
	for (int i = 0; i < roomNum; i++) {
		for (int j = 0; j < rooms[i].doorNum; j++) {
			cnt++;
			if (rand() % 2) {
				rooms[i].doors[j].xPos = rand() % 2 ? rooms[i].in.left : rooms[i].in.right;
				if (rooms[i].doors[j].xPos == 0)
					rooms[i].doors[j].xPos = rooms[i].in.right;
				if (rooms[i].doors[j].xPos == size - 1)
					rooms[i].doors[j].xPos = rooms[i].in.left;
				rooms[i].doors[j].yPos = rooms[i].in.top + rand() % (rooms[i].in.bottom - rooms[i].in.top - 1) + 1;
			}
			else {
				rooms[i].doors[j].yPos = rand() % 2 ? rooms[i].in.top : rooms[i].in.bottom;
				if (rooms[i].doors[j].yPos == 0)
					rooms[i].doors[j].yPos = rooms[i].in.bottom;
				if (rooms[i].doors[j].yPos == size - 1)
					rooms[i].doors[j].yPos = rooms[i].in.top;
				rooms[i].doors[j].xPos = rooms[i].in.left + rand() % (rooms[i].in.right - rooms[i].in.left - 1) + 1;
			}
			for (int k = 0; k < j|| 0*
				printf("%d : 문 생성 : (%d, %d)\n",i, rooms[i].doors[j].xPos, rooms[i].doors[j].yPos); k++) {
				if ((rooms[i].doors[k].xPos == rooms[i].doors[j].xPos&&
					rooms[i].doors[k].yPos <= rooms[i].doors[j].yPos+1&&
					rooms[i].doors[k].yPos >= rooms[i].doors[j].yPos-1)
					||
					(rooms[i].doors[k].yPos == rooms[i].doors[j].yPos&&
					rooms[i].doors[k].xPos <= rooms[i].doors[j].xPos + 1 &&
					rooms[i].doors[k].xPos >= rooms[i].doors[j].xPos - 1)) {
					j--;
					break;
				}
			}
			if (cnt == 10000000) {
				return 1;
			}
		}
	}
	return 0;
}

int makeDoor(int ***map,const int size,room* rooms,const int roomNum) {
	int numofDoors = (roomNum/2 * 3 + (roomNum-roomNum/2) * 2)/2*2;
	printf("만들 문의 갯수 : %d\n", numofDoors);
	int door3Cnt = numofDoors - roomNum * 2 , door2Cnt=roomNum-door3Cnt;
	printf("문이 3개인 방의 갯수 : %d\n", door3Cnt);
	printf("문이 2개인 방의 갯수 : %d\n", door2Cnt);
	while (1) {
		for (int i = 0; i < roomNum; i++) {
			if (i < door3Cnt) {
				rooms[i].doorNum = 3;
				rooms[i].doors = (door*)malloc(sizeof(door) * 3);
			}
			else {
				rooms[i].doorNum = 2;
				rooms[i].doors = (door*)malloc(sizeof(door) * 2);
			}
		}
		if (initializeDoor(rooms, roomNum, size)) {
			printf("문을 만드는 것을 실패하였습니다. 문만들기를 다시 시도합니다.\n");
		}
		else break;
	}
	return door3Cnt;
}
struct point { int x, y, cnt, pastIndex; };
void bfsRand1(	int*** map, int ***gone, const int size,
				point *queue, int &top, int &bottom,
				int nowX, int nowY, int nowCnt) {
	if ((nowX + 1<size)
		&& ((*map)[nowX + 1][nowY] == 0 || (*map)[nowX + 1][nowY] == 5)
		&& (!(*gone)[nowX + 1][nowY])) {
		queue[top++] = { nowX + 1,nowY,nowCnt + 1,bottom - 1 };
		(*gone)[nowX + 1][nowY] = 1;
	}
}
void bfsRand2(	int*** map, int ***gone, const int size,
				point *queue, int &top, int &bottom,
				int nowX, int nowY, int nowCnt) {
	if ((nowY + 1<size)
		&& ((*map)[nowX][nowY + 1] == 0 || (*map)[nowX][nowY + 1] == 5)
		&& (!(*gone)[nowX][nowY + 1])) {
		queue[top++] = { nowX,nowY + 1,nowCnt + 1 ,bottom - 1 };
		(*gone)[nowX][nowY] = 1;
	}
}
void bfsRand3(	int*** map, int ***gone, const int size,
				point *queue, int &top, int &bottom,
				int nowX, int nowY, int nowCnt) {
	if ((nowX - 1 >= 0)
		&& ((*map)[nowX - 1][nowY] == 0 || (*map)[nowX - 1][nowY] == 5)
		&& (!(*gone)[nowX - 1][nowY])) {
		queue[top++] = { nowX - 1,nowY,nowCnt + 1 ,bottom - 1 };
		(*gone)[nowX - 1][nowY] = 1;
	}
}
void bfsRand4(	int*** map, int ***gone, const int size,
				point *queue, int &top, int &bottom,
				int nowX, int nowY, int nowCnt) {
	if ((nowY - 1 >= 0)
		&& ((*map)[nowX][nowY - 1] == 0 || (*map)[nowX][nowY - 1] == 5)
		&& (!(*gone)[nowX][nowY - 1])) {
		queue[top++] = { nowX,nowY - 1,nowCnt + 1 ,bottom - 1 };
		(*gone)[nowX][nowY - 1] = 1;
	}
}
void searchDoorPosition(int ***map, const int size, room* rooms, const int roomNum,int roomIndex,int doorIndex) {
	struct point *queue=(struct point*)malloc(sizeof(struct point)*100000);
	int **gone = (int**)malloc(sizeof(int*)*size);
	for (int i = 0; i < size; i++) {
		gone[i] = (int*)malloc(sizeof(int)*size);
		for (int j = 0; j < size; j++) {
			gone[i][j] = 0;
		}
	}
	int top = 0, bottom = 0;
	queue[top++] = { rooms[0].doors[0].xPos, rooms[0].doors[0].yPos ,0,-1};
	gone[queue[0].x][queue[0].y] = 1;
	void(*bfsFunc[4])(	int ***,int ***,const int,
						point*, int&,int&,
						int, int, int) = {
											bfsRand1,
											bfsRand2,
											bfsRand3,
											bfsRand4
						};
	while (top > bottom) {
		int nowCnt = queue[bottom].cnt;
		int nowX = queue[bottom].x;
		int nowY = queue[bottom++].y;
		if ((nowX == rooms[rooms[roomIndex].doors[doorIndex].linkedRoomNum]
				.doors[rooms[roomIndex].doors[doorIndex].linkedRoomDoorNum].xPos+1&&
			nowY == rooms[rooms[roomIndex].doors[doorIndex].linkedRoomNum]
				.doors[rooms[roomIndex].doors[doorIndex].linkedRoomDoorNum].yPos)
			||
			(nowX == rooms[rooms[roomIndex].doors[doorIndex].linkedRoomNum]
				.doors[rooms[roomIndex].doors[doorIndex].linkedRoomDoorNum].xPos - 1 &&
			nowY == rooms[rooms[roomIndex].doors[doorIndex].linkedRoomNum]
				.doors[rooms[roomIndex].doors[doorIndex].linkedRoomDoorNum].yPos)
			||
			(nowX == rooms[rooms[roomIndex].doors[doorIndex].linkedRoomNum]
				.doors[rooms[roomIndex].doors[doorIndex].linkedRoomDoorNum].xPos&&
			nowY == rooms[rooms[roomIndex].doors[doorIndex].linkedRoomNum]
				.doors[rooms[roomIndex].doors[doorIndex].linkedRoomDoorNum].yPos+1)
			||
			(nowX == rooms[rooms[roomIndex].doors[doorIndex].linkedRoomNum]
				.doors[rooms[roomIndex].doors[doorIndex].linkedRoomDoorNum].xPos&&
			nowY == rooms[rooms[roomIndex].doors[doorIndex].linkedRoomNum]
				.doors[rooms[roomIndex].doors[doorIndex].linkedRoomDoorNum].yPos-1)) {
			printf("%d번 방의 %d번 문과 %d번 방의 %d번 문이 닿는데 걸린 거리 : %d\n", roomIndex,doorIndex,
				rooms[roomIndex].doors[doorIndex].linkedRoomNum,rooms[roomIndex].doors[doorIndex].linkedRoomDoorNum,nowCnt);
			struct point pt = queue[--bottom];
			while (
				//pt.x!=rooms[roomIndex].doors[doorIndex].xPos&&
				//pt.y!=rooms[roomIndex].doors[doorIndex].yPos
				pt.cnt
				) {
				(*map)[pt.x][pt.y] = 5;
				pt = queue[pt.pastIndex];
			}
			break;
		}
		int seq[4] = {};
		for (int i = 0; i < 4; i++) {
			seq[i] = rand() % 4;
			for (int j = 0; j < i; j++) {
				if (seq[i] == seq[j]) {
					i--;
					break;
				}
			}
		}
		bfsFunc[seq[0]](map, &gone, size, queue, top, bottom, nowX, nowY, nowCnt);
		bfsFunc[seq[1]](map, &gone, size, queue, top, bottom, nowX, nowY, nowCnt);
		bfsFunc[seq[2]](map, &gone, size, queue, top, bottom, nowX, nowY, nowCnt);
		bfsFunc[seq[3]](map, &gone, size, queue, top, bottom, nowX, nowY, nowCnt);
	}
}

void linkDoor(int*** map,const int size, room* rooms,const int roomNum,int doors3Num){
	for (int doorNum = 3; doorNum > 0; doorNum--) {
		for (int i = 0; i < roomNum; i++) {
			if (rooms[i].doorNum == doorNum) {
				int k=rand()%roomNum;
				while (k == i||rooms[k].doorNum==0) {
					k = rand() % roomNum;
				}
				rooms[i].doors[--rooms[i].doorNum].linkedRoomNum = k;
				rooms[i].doors[rooms[i].doorNum].linkedRoomDoorNum = --rooms[k].doorNum;
				rooms[k].doors[rooms[k].doorNum].linkedRoomNum = i;
				rooms[k].doors[rooms[k].doorNum].linkedRoomDoorNum = rooms[i].doorNum;
				printf("%d번 방의 %d번 문과 %d번 방의 %d번 문이 연결되었습니다.\n", i,rooms[i].doorNum, k,rooms[k].doorNum);
				(*map)[rooms[i].doors[rooms[i].doorNum].xPos][rooms[i].doors[rooms[i].doorNum].yPos] = 3;
				(*map)[rooms[k].doors[rooms[k].doorNum].xPos][rooms[k].doors[rooms[k].doorNum].yPos] = 4;
			}
		}
	}
	for (int i = 0; i < roomNum; i++) {
		rooms[i].doorNum = i < doors3Num ? 3 : 2;
	}
	for (int i = 0; i < roomNum; i++) {
		for (int j = rooms[i].doorNum - 1; j >= 0;j--) {
				searchDoorPosition(map, size, rooms, roomNum, i, j);
			
		}
	}
}

void createRoom(int ***map,const int size) {
	const int roomNum = size*size / 150; //std 30 : 6 50 : 16 70 :32
	printf("만들 방의 갯수 : %d\n", roomNum);
	room *rooms = (room*)malloc(sizeof(room)*roomNum);
	while (1) {
		if (setRoomPos(map, size, rooms, roomNum)) {
			printf("방을 만드는 과정에서 문제가 발생했습니다. 방만들기를 다시 시작합니다.");
		}
		else break;
	}
	int tmp=makeDoor(map, size, rooms, roomNum);
	for (int i = 0; i < roomNum; i++) {
		for (int j = 0; j < rooms[i].doorNum; j++) {
			(*map)[rooms[i].doors[j].xPos][rooms[i].doors[j].yPos] = 1;
		}
	}
	linkDoor(map, size, rooms, roomNum,tmp);
}

int** buildMap(const int size) {
	unsigned int seed = (size_t)time(NULL);
	printf("Seed : %u\n", seed);
	srand(seed);
	if (size < 30||size>70)return NULL;
	int** map=NULL;
	intialize(&map, size);
	createRoom(&map, size);

	printf("Map을 리턴합니다.");
	int k;
	scanf("%d", &k);
	return map;
}