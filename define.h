#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BinaryNode{
	char	*name;
	int		level;
	struct BinaryNode*	child;
	struct BinaryNode*	sibling;
};

typedef struct BinaryNode 	BinaryTree;
typedef BinaryTree*			BinaryTreePtr;

struct ListNode{
	char	*parent;
	char	*name;
	int		age;
	int 	gender;
	struct ListNode* 	next;
};

typedef struct ListNode		LinkedList;
typedef LinkedList*			LinkedListPtr;

struct StackNode{
	BinaryTreePtr Data;
	struct StackNode *next;
};

typedef struct StackNode	Stack;
typedef	Stack*				StackPtr;
