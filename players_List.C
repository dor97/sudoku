#include "players_List.h"

void insertDataToEndList(PlayersList* lst, char name[], short board[][SIZE], Array*** possibilities)
{
	Player* res = createNewListNode(name, board, possibilities, NULL, NULL);
	insertNodeToEndList(lst, res);
}

Player* createNewListNode(char name[], short board[][SIZE], Array*** possibilities, Player* prev, Player* next)
{
	Player* pl = (Player*)malloc(sizeof(Player));
	checkAllocation(pl);

	strcpy(pl->name, name);
	copyBoard(pl->sudukoBoard, board);

	pl->possibilities = possibilities;
	pl->next = next;
	pl->prev = prev;

	return pl;
}

void insertNodeToEndList(PlayersList* lst, Player* newTail)
{
	if (isEmptyList(*lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		newTail->prev = lst->tail;
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void removePlayerNode(PlayersList* corList, Player* toRemove)
{
	Player* temp;
	if (corList->head == corList->tail) // remove the only one node in lst
	{
		freePossibilityBoard(toRemove->possibilities);
		free(corList->head);
		corList->head = corList->tail = NULL;
	}
	else if (toRemove->prev == NULL) // remove first node
	{
		corList->head = corList->head->next;
		freePossibilityBoard(toRemove->possibilities);
		free(toRemove);
		corList->head->prev = NULL;
	}
	else if (toRemove == corList->tail) // remove last node
	{
		corList->tail = toRemove->prev;
		freePossibilityBoard(toRemove->possibilities);
		free(toRemove);
		corList->tail->next = NULL;
	}
	else // remove middle node
	{
		temp = toRemove->prev;
		temp->next = toRemove->next;
		temp = toRemove->next;
		temp->prev = toRemove->prev;
		freePossibilityBoard(toRemove->possibilities);
		free(toRemove);
	}
}

void makeEmptyList(PlayersList* lst)
{
	lst->head = lst->tail = NULL;
}

bool isEmptyList(PlayersList lst)
{
	return (lst.head == NULL);
}
