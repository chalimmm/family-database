#include "string_processing.h"

void			stack_push		(StackPtr *stack, BinaryTreePtr Family);
BinaryTreePtr	stack_pop		(StackPtr *stack);
void 			insert_list		(LinkedListPtr *sPtr, char* parent, char* name, int gender, int age);
BinaryTreePtr 	create_tree		(LinkedListPtr People, char* parent, int level);

/* Push to stack method */
void stack_push(StackPtr *stack, BinaryTreePtr Family){
	StackPtr node;
	
	node = malloc(sizeof(StackPtr));
	
	if(node == NULL){
		perror("  Memory not allocated ");
		return;
	}
	
	node->Data 	= Family;
	node->next 	= *stack;
	*stack 		= node;
}
/* Pop from stack method */
BinaryTreePtr stack_pop(StackPtr *stack){
	StackPtr temp;
	BinaryTreePtr value;
	
	temp	= *stack;
	value	= (*stack)->Data;
	*stack	= (*stack)->next;
	free(temp);
	
	return value;
}
/* Insert New Person to linked list in sorted order */
void insert_list(LinkedListPtr *sPtr,  char *parent, char *name, int gender, int age){
	LinkedListPtr newPtr;			// pointer to new Person in list
	LinkedListPtr previousPtr;		// pointer to previous Person in list
	LinkedListPtr currentPtr;		// pointer to current Person in list
	
	newPtr = (LinkedListPtr) malloc(sizeof(LinkedList));
	printf("  Inserting %s to list \n", name);
	if(newPtr != NULL){
		if(!(newPtr->name = (char*) malloc(sizeof(char) * (strlen(name)+1)))){
			perror("  Memory not allocated ");
			return;
		}
		Trim(name);
		Capitalize(name);
		strcpy(newPtr->name, name);
		
		newPtr->gender = gender;
		newPtr->age  = age;
		
		if(!(newPtr->parent = (char*) malloc(sizeof(char) * (strlen(parent)+1)))){
			perror("  Memory not allocated ");
			return;
		}
		Trim(parent);
		Capitalize(parent);
		strcpy(newPtr->parent, parent);
		
		newPtr->next = NULL;
		previousPtr  = NULL;
		currentPtr   = *sPtr;
		while(currentPtr != NULL && strcmp(parent, currentPtr->parent) >= 0){
			if(strcmp(parent, currentPtr->parent) == 0 && age >= currentPtr->age){
				break;
			}
			previousPtr = currentPtr;				// Finding position to insert
			currentPtr  = currentPtr->next;
		}
		
		if(previousPtr == NULL){					// insert at beginning
			newPtr->next = *sPtr;
			*sPtr = newPtr;
		}
		else{										// insert between previousPtr and currentPtr
			previousPtr->next = newPtr;
			newPtr->next = currentPtr;
		}
		printf("  %s has present in the list \n", name);
	}
	else{
		perror("  Memory not allocated ");
	}
}
/* Inserting new data to binary tree */
BinaryTreePtr create_tree(LinkedListPtr People, char* name, int level){
	BinaryTreePtr Parent;
	Parent = (BinaryTreePtr) malloc(sizeof(BinaryTree));
	
	if(Parent != NULL){
		while(!(Parent->name = (char*) malloc(sizeof(char) * (strlen(name)+1)))){
			perror("  Memory not allocated ");
		}
		strcpy(Parent->name, name);
		Parent->level = level;
		printf("  Inserting %s to Binary Tree Level %d\n", Parent->name, Parent->level);
		// Add Right Child
		LinkedListPtr Sibling = People;
		while(Sibling != NULL && strcmp(Sibling->name, name) != 0){
			Sibling = Sibling->next;	
		}
		if(Sibling != NULL && Sibling->next != NULL && strcmp(Sibling->parent, Sibling->next->parent) == 0){
			printf("  %s has sibling %s\n", Sibling->name, Sibling->next->name);
			Parent->sibling = create_tree(People, Sibling->next->name, level);
		}
		else Parent->sibling = NULL;
		// Add Down Child
		LinkedListPtr Child = People;
		while(Child != NULL && strcmp(Child->parent, name) != 0){
			Child = Child->next;	
		}
		if(Child != NULL){
			printf("  %s has child %s\n", name, Child->name);
			Parent->child = create_tree(People, Child->name, level+1);
		}
		else Parent->child = NULL;
		char c[30], s[30];
		c[0] = '\0';
		s[0] = '\0';
		if(Parent->child == NULL) strcpy(c, "NO_CHILD");
		else strcpy(c, Parent->child->name);
		if(Parent->sibling == NULL) strcpy(s, "NO_CHILD");
		else strcpy(s, Parent->sibling->name);
		printf("  Succesfully add %-30s %-30s %-30s %-10d\n", Parent->name, c, s, Parent->level);
	}
	else{
		perror("  Memory not allocated ");
	}
	
	return Parent;
}

