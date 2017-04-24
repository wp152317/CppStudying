#pragma once
#define MIN_SIZE 20
#define MAX_SIZE 200
/**
*	Name : buildMap
*	맵을 만들어서 리턴해주는 함수
*	Parameter
*	|-size : 리턴할 맵의 크기
*	|-seedNum : seed값을 넘겨야할때 쓰는 함수(default : NULL)
*/
int** buildMap(const int size,unsigned int* seedNum = 0);
