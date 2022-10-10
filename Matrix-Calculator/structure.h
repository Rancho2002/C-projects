#pragma once
#define ROWS 10
#define COLS 10
#define Volume_s 30
#define Volume_c 30
#include <stdio.h>

struct Matrix
{
	char name;
	float value[ROWS][COLS];
	int row;
	int col;
};

struct Matrix store[Volume_s];
struct Matrix count[Volume_c];
