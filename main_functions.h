#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "assistance_functions.h"
#include "free_functions.h"
#include "players_List.h"
#include "Random_board_functions.h"
#include "structs.h"

// Main Functions 
Array*** PossibleDigits(short sudokuBoard[][9]);
void creatArrayP(Array** array);
void initCellPossibilities(Array** array, short sudokuBoard[][9], int row, int col);
void removePossibility(Array** array);
int OneStage(short board[][SIZE], Array*** possibilities, int* x, int* y);
//int FillBoard(short board[][SIZE], Array*** possibilities);
void updatePossibilities(short board[][SIZE], Array*** possibilities, int row, int col);
void updateCellPossibilities(short board[][SIZE], Array*** possibilities, int row, int col, int delPossibility);
PlayersList makeActivePlayersList(int* size);
Player** makePointersArrToList(PlayersList* lst, int size);
