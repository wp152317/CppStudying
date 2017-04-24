#include "MapBuilder.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

///방의 위치를 지정하는 직사각형
typedef struct Rectangle {
	int left, top, bottom, right;
}rect;
///방에 달린 문
typedef struct Door {
	int xPos, yPos;
	int linkedRoomNum;
	int linkedRoomDoorNum;
}door;
///방
typedef struct Room{
	rect in;
	int doorNum;
	door* doors;
}room;

/**
*	Name : initialize
*	메모리에 맵을 할당하는 함수
*	Parameter
*	|-map : 리턴할 맵
*	|-size : 맵의 최대 크기
*/
void intialize(int ***map, const int size) {
	*map= (int**)malloc(sizeof(int*)*size);
	for (int i = 0; i < size; i++) {
		(*map)[i] = (int*)malloc(sizeof(int)*size);
		for (int j = 0; j < size; j++) {
			(*map)[i][j] = 0;
		}
	}
}
/**
*	Name : isOverlapRoom
*	방들이 겹치는지를 판단하는 함수
*	Parameter
*	|-desc : 기준 값이 되는 방
*	|-src : 비교 값이 되는 방
*/
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
/**
*	Name : initializeRoom
*	방의 위치를 넣는 함수
*	Parameter
*	|-src : 위치를 초기화할 방
*	|-size : 맵의 크기
*/
void initializeRoom(room* src,const int size) {
	src->in.top=rand() % (size - 7);
	src->in.left = rand() % (size - 7);
	src->in.bottom = src->in.top + 5 + rand() % 3;
	src->in.right = src->in.left + 5 + rand() % 3;
}
/**
*	Name : setRoomPos
*	방들의 위치를 지정하는 함수
*	Parameter
*	|-map : 리턴할 맵
*	|-size : 맵의 최대 크기
*	|-rooms : 문을 이을 방들
*	|-roomNum : 방들의 수
*/
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
/**
*	Name : initiallizeDoor
*	방의 문들을 만들어 주는 함수
*	Parameter
*	|-rooms : 문을 이을 방들
*	|-roomNum : 방들의 수
*	|-size : 맵의 최대 크기
*/
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
				printf("%d : 문 생성 : (%d, %d)\n",i, rooms[i].doors[j].xPos, rooms[i].doors[j].yPos)
				; k++) {
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
/**
*	Name : MakeDoor
*	만들 문의 갯수를 구하고 해당양의 문을 만드는 함수
*	Parameter
*	|-map : 리턴할 맵
*	|-size : 맵의 최대 크기
*	|-rooms : 문을 이을 방들
*	|-roomNum : 방들의 수
*/
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
///bfs를 돌리기 위한 구조체
struct point { int x, y, cnt, pastIndex; };
/**
*	Name : bfsRand(1,2,3,4)
*	문과 문사이를 잇기위한 bfs의 위치 파악 함수
*	Parameter
*	|-map : 리턴할 맵
*	|-gone : 방문 여부를 판단하는 배열
*	|-size : 맵의 최대 크기
*	|-queue : bfs에 쓰이는 큐
*	|-top : queue의 top pointer
*	|-bottom : queue의 bottom pointer
*	|-nowX : 현재의 X좌표
*	|-nowY : 현재의 Y좌표
*	|-nowCnt : 현재 첫점으로부터 온 거리
*	1-오른쪽
*	2-아래쪽
*	3-왼쪽
*	4-위쪽
*/
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
/**
*	Name : searchDoorPosition
*	방의 문들이 이어지게끔 길을 찾는 함수
*	Parameter
*	|-map : 리턴할 맵
*	|-size : 맵의 최대 크기
*	|-rooms : 문을 이을 방들
*	|-roomNum : 방들의 수
*	|-roomIndex : 방 번호
*	|-doorIndex : 방의 문 번호
*/
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
		if (
		   ((nowX == rooms[rooms[roomIndex].doors[doorIndex].linkedRoomNum]
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
				.doors[rooms[roomIndex].doors[doorIndex].linkedRoomDoorNum].yPos-1)
			)) {
			printf("%d번 방의 %d번 문과 %d번 방의 %d번 문이 닿는데 걸린 거리 : %d\n", roomIndex,doorIndex,
				rooms[roomIndex].doors[doorIndex].linkedRoomNum,rooms[roomIndex].doors[doorIndex].linkedRoomDoorNum,nowCnt);
			struct point pt = queue[--bottom];
			struct point pw=pt;
			while (
				//pt.x!=rooms[roomIndex].doors[doorIndex].xPos&&
				//pt.y!=rooms[roomIndex].doors[doorIndex].yPos
				pt.cnt
				) {
				if ((pt.x + 1<size && (*map)[pt.x + 1][pt.y] == 5 && pt.x + 1 != pw.x&&pt.y != pw.y)||
					(pt.x - 1>= 0  && (*map)[pt.x - 1][pt.y] == 5 && pt.x - 1 != pw.x&&pt.y != pw.y)||
					(pt.y + 1<size &&(*map)[pt.x][pt.y + 1] == 5 && pt.x != pw.x&&pt.y != pw.y + 1) ||
					(pt.y - 1>= 0  &&(*map)[pt.x][pt.y - 1] == 5 && pt.x != pw.x&&pt.y != pw.y - 1)) {
					(*map)[pt.x][pt.y] = 5;
					return;
				}
				(*map)[pt.x][pt.y] = 5;
				pw = pt;
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
/**
*	Name : linkDoor
*	방의 문들을 이어주는 함수
*	Parameter
*	|-map : 리턴할 맵
*	|-size : 맵의 최대 크기
*	|-rooms : 문을 이을 방들
*	|-roomNum : 방들의 수
*	|-door3Num : 문이 3개있는 방의 갯수
*/
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
/**
*	Name : CreateRoom
*	방을 만드는 함수
*	Parameter
*	|-map : 리턴할 맵
*	|-size : 맵의 최대 크기
*/
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
	(*map)	[rooms[0].in.left + rand()%(rooms[0].in.right-rooms[0].in.left-1)+1]
			[rooms[0].in.top + rand() % (rooms[0].in.bottom - rooms[0].in.top - 1) + 1] = 7;
	(*map)	[rooms[roomNum - 1].in.left + rand() % 
		(rooms[roomNum - 1].in.right - rooms[roomNum - 1].in.left - 1) + 1]
			[rooms[roomNum - 1].in.top + rand() % 
		(rooms[roomNum - 1].in.bottom - rooms[roomNum - 1].in.top - 1) + 1] = 8;
	int tmp=makeDoor(map, size, rooms, roomNum);
	for (int i = 0; i < roomNum; i++) {
		for (int j = 0; j < rooms[i].doorNum; j++) {
			(*map)[rooms[i].doors[j].xPos][rooms[i].doors[j].yPos] = 1;
		}
	}
	linkDoor(map, size, rooms, roomNum,tmp);
}
/**
 *	Name : SolidRoad
 *	연결된 길의 주변에 벽을 놓아주는 함수
 *	Parameter
 *	|-map : 리턴할 맵
 *	|-size : 맵의 최대 크기
 */
void solidRoad(int ***map,const int size) {
	for (int i = 1; i < size-1; i++) {
		for (int j = 1; j < size-1; j++) {
			if ((*map)[i][j] == 5) {
				if (!(*map)[i - 1][j]) {
					(*map)[i - 1][j] = 6;
				}if (!(*map)[i][j-1]) {
					(*map)[i][j-1] = 6;
				}if (!(*map)[i + 1][j]) {
					(*map)[i + 1][j] = 6;
				}if (!(*map)[i][j+1]) {
					(*map)[i][j+1] = 6;
				}if (!(*map)[i - 1][j - 1]) {
					(*map)[i - 1][j - 1] = 6;
				}if (!(*map)[i - 1][j + 1]) {
					(*map)[i - 1][j + 1] = 6;
				}if (!(*map)[i + 1][j - 1]) {
					(*map)[i + 1][j - 1] = 6;
				}if (!(*map)[i + 1][j + 1]) {
					(*map)[i + 1][j + 1] = 6;
				}
			}
		}
		if ((*map)[i][0] == 5) {
			if (!(*map)[i - 1][0]) {
				(*map)[i - 1][0] = 6;
			}if (!(*map)[i + 1][0]) {
				(*map)[i + 1][0] = 6;
			}if (!(*map)[i][1]) {
				(*map)[i][1] = 6;
			}
		}if ((*map)[i][size-1] == 5) {
			if (!(*map)[i - 1][size - 1]) {
				(*map)[i - 1][size - 1] = 6;
			}if (!(*map)[i + 1][size - 1]) {
				(*map)[i + 1][size - 1] = 6;
			}if (!(*map)[i][size - 2]) {
				(*map)[i][size - 2] = 6;
			}
		}if ((*map)[0][i] == 5) {
			if (!(*map)[0][i-1]) {
				(*map)[0][i - 1] = 6;
			}if (!(*map)[0][i + 1]) {
				(*map)[0][i + 1] = 6;
			}if (!(*map)[1][i]) {
				(*map)[1][i] = 6;
			}
		}if ((*map)[size - 1][i] == 5) {
			if (!(*map)[size - 1][i - 1]) {
				(*map)[size - 1][i - 1] = 6;
			}if (!(*map)[size - 1][i + 1]) {
				(*map)[size - 1][i + 1] = 6;
			}if (!(*map)[size - 2][i]) {
				(*map)[size - 2][i] = 6;
			}
		}
	}
}
/**
*	Name : buildMap
*	맵을 만들어서 리턴해주는 함수
*	Parameter
*	|-size : 리턴할 맵의 크기
*	|-seedNum : seed값을 넘겨야할때 쓰는 함수(default : NULL)
*/
int** buildMap(const int size,unsigned int* seedNum) {
	unsigned int seed = (size_t)time(NULL);
	//seed =\
		1493026259				\
	;
	printf("Seed : %u\n", seed);
	
	srand(seed);
	if(seedNum!=NULL)
		*seedNum = seed;
	if (size < MIN_SIZE||size>MAX_SIZE)return NULL;
	int** map=NULL;
	intialize(&map, size);
	createRoom(&map, size);
	solidRoad(&map, size);
	printf("Map을 리턴합니다.");
	_getch();
	return map;
}