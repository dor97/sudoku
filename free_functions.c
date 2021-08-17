#include "free_functions.h"

void freeProject(PlayersList* activePlayersList, PlayersList* winList, Tree tr, Player** pArr)
{
	freePlayersList(activePlayersList);
	freePlayersList(winList);
	freeTree(tr);
	free(pArr);
}

void freePlayersList(PlayersList* lst)
{
	Player* curr = lst->head, * next;

	while (curr != NULL)
	{
		next = curr->next;
		if (curr->possibilities != NULL)
			freePossibilityBoard(curr->possibilities);

		free(curr);
		curr = next;
	}
}

void freeDList(DList* dList)
{
	DListNode* curr = dList->head, * next;

	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}

void freePossibilityBoard(Array*** PossibleDigits)
{
	int i, j;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
			freeArray(PossibleDigits[i][j]);
	}

	for (i = 0; i < SIZE; i++)
		free(PossibleDigits[i]);

	free(PossibleDigits);
}

void freeArray(Array* cell)
{
	if (cell != NULL)
	{
		free(cell->arr);
	}

	free(cell);
}

void freeTree(Tree tr)
{
	freeTreeRec(tr.root);
}

void freeTreeRec(TreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		freeTreeRec(root->left);
		freeTreeRec(root->right);
		free(root);
	}
}