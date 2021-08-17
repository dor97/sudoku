#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "DList.h"
//#include "assistance_functions.h"
#include "free_functions.h"
#include "main_functions.h"
#include "structs.h"

/*
// Constants 
#define MAX_LEN_NAME 101
#define FINISH_SUCCESS 0
#define NOT_FINISH 1
#define FINISH_FAILURE 2
#define FILLED 1
#define FAIL -1
#define SIZE 9
#define INVALID 0 
#define VALID 1
#define NOT_FOUND -1

// Structs 
typedef struct _Cell {
	int x;
	int y;
}Cell;

typedef struct dlistnode
{
	Cell c;
	struct dlistnode* next;
	struct dlistnode* prev;

}DListNode;

typedef struct dlist
{
	DListNode* head;
	DListNode* tail;
}DList;

typedef struct _Array
{
	short* arr;
	unsigned short size;
}Array;

typedef struct _Player
{
	char name[MAX_LEN_NAME];
	short sudukoBoard[SIZE][SIZE];
	Array*** possibilities;
	struct _Player* next;
	struct _Player* prev;
}Player;

typedef struct _playersList
{
	Player* head;
	Player* tail;
}PlayersList;

typedef struct treeNode
{
	Player** data;
	struct treeNode* left;
	struct treeNode* right;
}TreeNode;

typedef struct tree
{
	TreeNode* root;
}Tree;
*/

// Random board functions
void initsudokoBoard(short board[][SIZE]);
void pickRan(short board[][SIZE], Array*** possible_solutions);
void removeDListNode(DList* corList, DListNode* toRemove);
void randomCell(short board[][SIZE], Array*** possibilities, Cell cl);
