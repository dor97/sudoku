#include "main_functions.h"



int OneStage(short board[][SIZE], Array*** possibilities, int* x, int* y)
{
	int i, j, countUnEmptyCell = 0, minPossibilities = SIZE + 1; // minPosibillities > max(possibilities[i][j]->size)
	bool filled_at_least_one_Cell = false;
	Cell tmpCell;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (board[i][j] == -1) // found empty cell
			{
				if (possibilities[i][j] == NULL) // empty cell that dont have any possibilities left
				{
					return FINISH_FAILURE;
				}
				else if (possibilities[i][j]->size == 1) // found cell that have only one possibility
				{
					board[i][j] = possibilities[i][j]->arr[0];
					possibilities[i][j]->arr[0] = 0; // init possibility for removing
					removePossibility(&possibilities[i][j]);
					updatePossibilities(board, possibilities, i, j);
					filled_at_least_one_Cell = true;
					countUnEmptyCell++;
				}
				else if (possibilities[i][j]->size < minPossibilities) // get the Cell with the minimum possibilities for case filled_at_least_one_Cell = false
				{
					minPossibilities = possibilities[i][j]->size;
					tmpCell.x = i;
					tmpCell.y = j;
				}
			}
			else
				countUnEmptyCell++;
		}
	}

	if (countUnEmptyCell == SIZE * SIZE) // the board is full and valid
		return FINISH_SUCCESS;
	else if (filled_at_least_one_Cell) // the board is not full, then scan again for Cell with only one possibility
	{
		return OneStage(board, possibilities, x, y);
	}
	else // there is no Cell with only one possibility and the board is not full
	{
		*x = tmpCell.x;
		*y = tmpCell.y;
		return NOT_FINISH;
	}
}

/*int FillBoard(short board[][SIZE], Array*** possibilities)
{
	int res, x, y;
	res = OneStage(board, possibilities, &x, &y);

	if (res == NOT_FINISH)
	{
		sudokoPrintBoard(board);
		printf("Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n", x, y);
		printPossibilities(possibilities, x, y);
		scanf("%hd", &board[x][y]);
		freeArray(possibilities[x][y]);
		possibilities[x][y] = NULL;
		printf("Updating cell %d with value %d\n\n", x * SIZE + y, board[x][y]);
		updatePossibilities(board, possibilities, x, y);
		return FillBoard(board, possibilities); // countinue fill board
	}
	else if (res == FINISH_SUCCESS)
	{
		return FILLED;
	}
	else // returned FINISH_FAILURE
	{
		return FAIL;
	}
}*/

void updatePossibilities(short board[][SIZE], Array*** possibilities, int row, int col)
{
	int i, j, delPossibility = board[row][col];

	for (i = 0; i < SIZE; i++) // update possibilities in the same Row
	{
		updateCellPossibilities(board, possibilities, row, i, delPossibility);
	}

	for (i = 0; i < SIZE; i++) // update possibilities in the same Col
	{
		updateCellPossibilities(board, possibilities, i, col, delPossibility);
	}

	// initialize row + col in order to update from the first cell in the square 3X3
	row = row - (row % 3);
	col = col - (col % 3);

	for (i = row; i < row + 3; i++) //update possibilities that in the same Square3X3
	{
		for (j = col; j < col + 3; j++)
		{
			updateCellPossibilities(board, possibilities, i, j, delPossibility);
		}
	}
}

void updateCellPossibilities(short board[][SIZE], Array*** possibilities, int row, int col, int delPossibility)
{
	int ind;

	if (board[row][col] == -1 && possibilities[row][col] != NULL)
	{
		ind = binarySearch(possibilities[row][col]->arr, possibilities[row][col]->size, delPossibility); // find the index of delPossibility in arr

		if (ind != NOT_FOUND)
		{
			possibilities[row][col]->arr[ind] = 0;
			removePossibility(&(possibilities[row][col]));
		}
	}
}

Array*** PossibleDigits(short sudokuBoard[][9])
{
	Array*** arr = (Array***)malloc(sizeof(Array**) * SIZE);
	checkAllocation(arr);

	int i = 0, j;
	for (i = 0; i < SIZE; i++)
	{
		arr[i] = (Array**)malloc(sizeof(Array*) * SIZE);
		checkAllocation(arr[i]);
	}


	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (sudokuBoard[i][j] == -1)
				creatArrayP(&arr[i][j]);
			//		initCellPossibilities(&arr[i][j], sudokuBoard, i, j);
			else
				arr[i][j] = NULL;
		}
	}
	pickRan(sudokuBoard, arr);
	return arr;
}

void creatArrayP(Array** array)
{
	int i;
	*array = (Array*)malloc(sizeof(Array));
	checkAllocation(*array);

	(*array)->arr = (short*)malloc(sizeof(short) * SIZE);
	checkAllocation((*array)->arr);

	for (i = 0; i < SIZE; i++) //create an array with all the digits
		(*array)->arr[i] = i + 1;
	(*array)->size = SIZE;

}

//create an Array(struct) in a cell of an array(arr) in PossibleDigits
void initCellPossibilities(Array** array, short sudokuBoard[][9], int row, int col)
{
	int i, j;

	for (i = 0; i < SIZE; i++)  //remove from the array all the digits that exist in the same col
		if (sudokuBoard[i][col] != -1)
			(*array)->arr[sudokuBoard[i][col] - 1] = 0;

	for (i = 0; i < SIZE; i++)  //remove from the array all the digits that exist in the same row
		if (sudokuBoard[row][i] != -1)
			(*array)->arr[sudokuBoard[row][i] - 1] = 0;

	for (i = 0; i < SIZE / 3; i++)  //remove from the array all the digits that exist in the 3X3 square
		for (j = 0; j < SIZE / 3; j++)
			if (sudokuBoard[row % 3 * 3 + i][col % 3 * 3 + j] != -1)
				(*array)->arr[sudokuBoard[(row - row % 3) + i][(col - col % 3) + j] - 1] = 0;

	removePossibility(array);
}

//remove all the emptey slot(contains zero)
void removePossibility(Array** array)
{
	int i, k = 0;
	for (i = 0; i + k < (*array)->size; i++)
	{
		while (i + k < (*array)->size && ((*array)->arr)[i + k] == 0) //if found zero advance k by one
			k++;
		if (k > 0 && i + k < (*array)->size)
			((*array)->arr)[i] = ((*array)->arr)[i + k];
	}

	if (k > 0 && k < (*array)->size)
		(*array)->arr = (short*)realloc((*array)->arr, ((*array)->size - k) * sizeof(short));

	(*array)->size = (*array)->size - k;

	if ((*array)->size == 0)
	{
		freeArray(*(array));
		*array = NULL;
	}
}

PlayersList makeActivePlayersList(int* size)
{
	PlayersList lst;
	Array*** possibilities;
	int numOfPlayers, i;
	char name[MAX_LEN_NAME];
	short board[SIZE][SIZE];

	makeEmptyList(&lst);

	printf("Please enter the number of players: ");
	scanf("%d", &numOfPlayers);
	getchar();

	for (i = 0; i < numOfPlayers; i++)
	{
		printf("\nPlayer %d, please enter your first name: ", i + 1);
		scanf("%s", name);

		initsudokoBoard(board);
		possibilities = PossibleDigits(board);

		insertDataToEndList(&lst, name, board, possibilities);
	}

	*size = numOfPlayers;

	return lst;
}

Player** makePointersArrToList(PlayersList* lst, int size)
{
	int i, newSize;
	Player* curr = lst->head;
	Player** playersArr = (Player**)malloc(sizeof(Player*) * size);
	checkAllocation(playersArr);

	for (i = 0; i < size; i++)
	{
		playersArr[i] = curr;
		curr = curr->next;
	}

	mergeSort(playersArr, size);

	newSize = pow(2, log(size + 1.0) / log(2)) - 1; // new size for tree players
	playersArr = realloc(playersArr, newSize * sizeof(Player));

	for (i = size; i < newSize; i++)
		playersArr[i] = NULL;

	return playersArr;
}
