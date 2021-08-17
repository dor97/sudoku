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
#include "structs.h"


//Active players List functions
void insertDataToEndList(PlayersList* lst, char name[], short board[][SIZE], Array*** possibilities);
Player* createNewListNode(char name[], short board[][SIZE], Array*** possibilities, Player* prev, Player* next);
void insertNodeToEndList(PlayersList* lst, Player* newTail);
void removePlayerNode(PlayersList* corList, Player* toRemove);
void makeEmptyList(PlayersList* lst);
bool isEmptyList(PlayersList lst);
