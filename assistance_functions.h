#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"

// assistance functions 
void mergeSort(Player* arr[], int size);
Player** merge(Player* a1[], int size1, Player* a2[], int size2);
void copyPlayersArr(Player* dest[], Player* src[], int size);
int countFullSquares(short board[][SIZE]);
void copyBoard(short dest[][SIZE], short src[][SIZE]);
void sudokoPrintBoard(short board[][SIZE]);
void printPossibilities(Array*** PossibleDigits, int x, int y);
void printWinners(PlayersList winList);
int binarySearch(short arr[], unsigned short size, int item);
void checkAllocation(void* ptr);
