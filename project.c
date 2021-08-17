#define _CRT_SECURE_NO_WARNINGS
#include "assistance_functions.h"
#include "Tree_functions.h"
#include"free_functions.h"
#include "players_List.h"
#include "main_functions.h"


void main()
{
	int size;
	PlayersList activePlayersList = makeActivePlayersList(&size);
	Player** pArr = makePointersArrToList(&activePlayersList, size);
	Tree tr = BuildTreeFromArray(pArr, size);
	PlayersList winList;

	makeEmptyList(&winList);

	printTreeInorder(tr, &activePlayersList, &winList);

	printWinners(winList);

	freeProject(&activePlayersList, &winList, tr, pArr);
}
