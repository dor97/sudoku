#include "Random_board_functions.h"


void initsudokoBoard(short board[][SIZE])
{
	int i, j;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			board[i][j] = -1;
		}
	}
}

void pickRan(short board[][SIZE], Array*** possible_solutions)
{
	int i = 0, j = 0, num, max;
	DListNode* curr;
	DList corList;
	Cell c;
	srand(time(NULL));

	max = rand() % 20 + 1;
	makeEmptyDList(&corList);

	for (i = 0; i < SIZE; i++)
	{
		c.x = i;
		for (j = 0; j < SIZE; j++)
		{
			c.y = j;
			insertDataToEndDList(&corList, c);
		}
	}

	for (j = 0; j < max; j++)
	{
		curr = corList.head;
		num = rand() % (81 - j) + 1;
		for (i = 1; i < num; i++)
			curr = curr->next;
		c = curr->c;
		removeDListNode(&corList, curr);
		randomCell(board, possible_solutions, c);
	}

	freeDList(&corList);
}

void randomCell(short board[][SIZE], Array*** possibilities, Cell cl)
{
	int size, randomInd;

	if (possibilities[cl.x][cl.y] != NULL)
	{
		size = possibilities[cl.x][cl.y]->size;
		randomInd = rand() % size; // get random index 
		board[cl.x][cl.y] = possibilities[cl.x][cl.y]->arr[randomInd];
		freeArray(possibilities[cl.x][cl.y]);
		possibilities[cl.x][cl.y] = NULL;
		updatePossibilities(board, possibilities, cl.x, cl.y);
	}
	else
	{

	}
}
