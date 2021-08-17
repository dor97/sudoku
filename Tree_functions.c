#include "Tree_functions.h"


Tree BuildTreeFromArray(Player** arr, int size)
{
	Tree tr;

	tr.root = BuildTreeFromArrayRec(arr, 0, size - 1);

	return tr;
}

TreeNode* BuildTreeFromArrayRec(Player** arr, int leftInd, int rightInd)
{
	int middle = (leftInd + rightInd) / 2;

	if (rightInd < leftInd || arr[middle] == NULL)
		return NULL;
	else
	{
		TreeNode* left, * right, * root;

		left = BuildTreeFromArrayRec(arr, leftInd, middle - 1);
		right = BuildTreeFromArrayRec(arr, middle + 1, rightInd);

		root = createNewTreeNode(&arr[middle], left, right);

		return root;
	}
}

TreeNode* createNewTreeNode(Player** data, TreeNode* left, TreeNode* right)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	checkAllocation(node);

	node->data = data;
	node->left = left;
	node->right = right;

	return node;
}

void printTreeInorder(Tree tr, PlayersList* activePlayersList, PlayersList* winList)
{
	while (!isEmptyList(*(activePlayersList)))
	{
		printTreeInorderRec(tr.root, activePlayersList, winList);
	}
}

void printTreeInorderRec(TreeNode* root, PlayersList* activePlayersList, PlayersList* winList)
{
	if (root == NULL)
		return;
	else
	{
		int x, y, res;

		printTreeInorderRec(root->left, activePlayersList, winList);

		if ((*root->data) != NULL)
		{
			res = OneStage((*root->data)->sudukoBoard, (*root->data)->possibilities, &x, &y);

			if (res == FINISH_FAILURE)
			{
				printf("%s selections led to duplications\n\n", (*root->data)->name);
				removePlayerNode(activePlayersList, (*root->data));
				(*root->data) = NULL;

			}
			else if (res == FINISH_SUCCESS)
			{
				printf("%s's board filled succesfully\n\n", (*root->data)->name);
				insertDataToEndList(winList, (*root->data)->name, (*root->data)->sudukoBoard, NULL);
				removePlayerNode(activePlayersList, (*root->data));
				(*root->data) = NULL;
			}
			else // res == NOT_FINISH
			{
				printf("%s turn: \n", (*root->data)->name);
				sudokoPrintBoard((*root->data)->sudukoBoard);
				printf("Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n", x, y);
				printPossibilities((*root->data)->possibilities, x, y);
				scanf("%hd", &(*root->data)->sudukoBoard[x][y]);
				freeArray((*root->data)->possibilities[x][y]);
				(*root->data)->possibilities[x][y] = NULL;
				printf("Updating cell %d with value %d\n\n", x * SIZE + y, (*root->data)->sudukoBoard[x][y]);
				updatePossibilities((*root->data)->sudukoBoard, (*root->data)->possibilities, x, y);
			}
		}

		printTreeInorderRec(root->right, activePlayersList, winList);

	}
}
