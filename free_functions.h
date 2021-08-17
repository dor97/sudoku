#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"

//free functions
void freeProject(PlayersList* activePlayersList, PlayersList* winList, Tree tr, Player** pArr);
void freePlayersList(PlayersList* lst);
void freeDList(DList* dList);
void freePossibilityBoard(Array*** PossibleDigits);
void freeArray(Array* cell);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);
