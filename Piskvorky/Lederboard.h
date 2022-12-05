#pragma once
#define NAME_SIZE 20
#include <iostream>

typedef struct
{
	int obsadene;
	char meno[NAME_SIZE];
	int pocetVyhier;
}leader;


void addToBoard(leader* LeaderBoard, char* meno);


void ShowBoard(leader LeaderBoard[10]);
