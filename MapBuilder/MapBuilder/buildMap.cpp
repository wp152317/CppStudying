#include "MapBuilder.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

///���� ��ġ�� �����ϴ� ���簢��
typedef struct Rectangle {
	int left, top, bottom, right;
}rect;
///�濡 �޸� ��
typedef struct Door {
	int xPos, yPos;
	int linkedRoomNum;
	int linkedRoomDoorNum;
}door;
///��
typedef struct Room{
	rect in;
	int doorNum;
	door* doors;
}room;

/**
*	Name : initialize
*	�޸𸮿� ���� �Ҵ��ϴ� �Լ�
*	Parameter
*	|-map : ������ ��
*	|-size : ���� �ִ� ũ��
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
*	����� ��ġ������ �Ǵ��ϴ� �Լ�
*	Parameter
*	|-desc : ���� ���� �Ǵ� ��
*	|-src : �� ���� �Ǵ� ��
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
*	���� ��ġ�� �ִ� �Լ�
*	Parameter
*	|-src : ��ġ�� �ʱ�ȭ�� ��
*	|-size : ���� ũ��
*/
void initializeRoom(room* src,const int size) {
	src->in.top=rand() % (size - 7);
	src->in.left = rand() % (size - 7);
	src->in.bottom = src->in.top + 5 + rand() % 3;
	src->in.right = src->in.left + 5 + rand() % 3;
}
/**
*	Name : setRoomPos
*	����� ��ġ�� �����ϴ� �Լ�
*	Parameter
*	|-map : ������ ��
*	|-size : ���� �ִ� ũ��
*	|-rooms : ���� ���� ���
*	|-roomNum : ����� ��
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
*	���� ������ ����� �ִ� �Լ�
*	Parameter
*	|-rooms : ���� ���� ���
*	|-roomNum : ����� ��
*	|-size : ���� �ִ� ũ��
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
				printf("%d : �� ���� : (%d, %d)\n",i, rooms[i].doors[j].xPos, rooms[i].doors[j].yPos)
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
*	���� ���� ������ ���ϰ� �ش���� ���� ����� �Լ�
*	Parameter
*	|-map : ������ ��
*	|-size : ���� �ִ� ũ��
*	|-rooms : ���� ���� ���
*	|-roomNum : ����� ��
*/
int makeDoor(int ***map,const int size,room* rooms,const int roomNum) {
	int numofDoors = (roomNum/2 * 3 + (roomNum-roomNum/2) * 2)/2*2;
	printf("���� ���� ���� : %d\n", numofDoors);
	int door3Cnt = numofDoors - roomNum * 2 , door2Cnt=roomNum-door3Cnt;
	printf("���� 3���� ���� ���� : %d\n", door3Cnt);
	printf("���� 2���� ���� ���� : %d\n", door2Cnt);
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
			printf("���� ����� ���� �����Ͽ����ϴ�. ������⸦ �ٽ� �õ��մϴ�.\n");
		}
		else break;
	}
	return door3Cnt;
}
///bfs�� ������ ���� ����ü
struct point { int x, y, cnt, pastIndex; };
/**
*	Name : bfsRand(1,2,3,4)
*	���� �����̸� �ձ����� bfs�� ��ġ �ľ� �Լ�
*	Parameter
*	|-map : ������ ��
*	|-gone : �湮 ���θ� �Ǵ��ϴ� �迭
*	|-size : ���� �ִ� ũ��
*	|-queue : bfs�� ���̴� ť
*	|-top : queue�� top pointer
*	|-bottom : queue�� bottom pointer
*	|-nowX : ������ X��ǥ
*	|-nowY : ������ Y��ǥ
*	|-nowCnt : ���� ù�����κ��� �� �Ÿ�
*	1-������
*	2-�Ʒ���
*	3-����
*	4-����
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
*	���� ������ �̾����Բ� ���� ã�� �Լ�
*	Parameter
*	|-map : ������ ��
*	|-size : ���� �ִ� ũ��
*	|-rooms : ���� ���� ���
*	|-roomNum : ����� ��
*	|-roomIndex : �� ��ȣ
*	|-doorIndex : ���� �� ��ȣ
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
			printf("%d�� ���� %d�� ���� %d�� ���� %d�� ���� ��µ� �ɸ� �Ÿ� : %d\n", roomIndex,doorIndex,
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
*	���� ������ �̾��ִ� �Լ�
*	Parameter
*	|-map : ������ ��
*	|-size : ���� �ִ� ũ��
*	|-rooms : ���� ���� ���
*	|-roomNum : ����� ��
*	|-door3Num : ���� 3���ִ� ���� ����
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
				printf("%d�� ���� %d�� ���� %d�� ���� %d�� ���� ����Ǿ����ϴ�.\n", i,rooms[i].doorNum, k,rooms[k].doorNum);
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
*	���� ����� �Լ�
*	Parameter
*	|-map : ������ ��
*	|-size : ���� �ִ� ũ��
*/
void createRoom(int ***map,const int size) {
	const int roomNum = size*size / 150; //std 30 : 6 50 : 16 70 :32
	printf("���� ���� ���� : %d\n", roomNum);
	room *rooms = (room*)malloc(sizeof(room)*roomNum);
	while (1) {
		if (setRoomPos(map, size, rooms, roomNum)) {
			printf("���� ����� �������� ������ �߻��߽��ϴ�. �游��⸦ �ٽ� �����մϴ�.");
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
 *	����� ���� �ֺ��� ���� �����ִ� �Լ�
 *	Parameter
 *	|-map : ������ ��
 *	|-size : ���� �ִ� ũ��
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
*	���� ���� �������ִ� �Լ�
*	Parameter
*	|-size : ������ ���� ũ��
*	|-seedNum : seed���� �Ѱܾ��Ҷ� ���� �Լ�(default : NULL)
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
	printf("Map�� �����մϴ�.");
	_getch();
	return map;
}