#pragma once
#define MIN_SIZE 20
#define MAX_SIZE 200
/**
*	Name : buildMap
*	���� ���� �������ִ� �Լ�
*	Parameter
*	|-size : ������ ���� ũ��
*	|-seedNum : seed���� �Ѱܾ��Ҷ� ���� �Լ�(default : NULL)
*/
int** buildMap(const int size,unsigned int* seedNum = 0);
