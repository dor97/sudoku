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

//DList functions
void makeEmptyDList(DList* dlst);
void insertNodeToEndDList(DList* dlst, DListNode* newTail);
void insertDataToEndDList(DList* lst, Cell c);
DListNode* createNewDListNode(Cell c, DListNode* next, DListNode* prev);
bool isEmptyDList(DList lst);
