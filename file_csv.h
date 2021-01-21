#include "data_structure.h"

void			guidebook		();
LinkedListPtr 	read_people		();
void 			write_people	(LinkedListPtr People);
BinaryTreePtr 	convert_family	(LinkedListPtr People);
void 			write_family	(BinaryTreePtr Family);
LinkedListPtr 	scan_people		(char* who);
int 			scan_family		(char* who);
void			print_list		();
void			print_tree		();

/* Read data from README.txt, parse per line, and display to console */
void guidebook(){
	FILE *fp = fopen("README.txt", "r");
	if(fp == NULL) perror("  Unable to open the file ");
	else{
		char line[1024];
		int lineNo;
		for(lineNo = 0; fgets(line, sizeof(line), fp); lineNo++){
			printf("  %s", line);
		}
	}
}
/* Read data from DataPeople.csv, parse it, and save to Linked List People*/
LinkedListPtr read_people(){
	LinkedListPtr dataPeople = NULL;
	
	FILE *fp = fopen("DataPeople.csv", "r");
	if(fp == NULL){
		perror("  Unable to read DataPeople.csv ");
		fclose(fp);
		return NULL;
	}
	else{
		perror("  Reading DataPeople.csv ... ");
		char line[1024];
		int lineNo;
		for(lineNo = 0; fgets(line, sizeof(line), fp); lineNo++){
			char name[30], parent[30], gender[10], age[10], err[10];
			name	[0] = '\0';		//reset string to null
			parent	[0] = '\0';
			gender	[0] = '\0';
			age		[0] = '\0';
			err		[0] = '\0';
			
			int cek = sscanf(line, "%[^;];%[^;];%[^;];%[^;];%s", parent, name, gender, age, err);
			if(cek < 5){
				printf("  ... Format error in line %-3d ...\n", lineNo);
				continue;
			}
			if(!lineNo) continue;
			insert_list(&dataPeople, parent, name, Convert(gender), Convert(age));		//insert new data to list
		}
	}
	fclose(fp);
	perror("  Reading succesful from DataPeople.csv ");
	return dataPeople;
}
/* Write data from linked list People to DataPeople.csv */
void write_people(LinkedListPtr People){
	FILE *fp = fopen("DataPeople.csv", "w");
	if(fp == NULL){
		perror("  Unable to write DataPeople.csv ");
		return;
	}
	else{
		perror("  Writing DataPeople.csv ");
		fprintf(fp, "PARENT;NAME;GENDER;AGE;ERROR\n");
		while(People != NULL){
			fprintf(fp, "%s;%s;%d;%d;%s\n", People->parent, People->name,  People->gender, People->age, "NO_ERROR");
			People = People->next;
		}
	}
	fclose(fp);
	perror("  Writing succesful to DataPeople.csv ");
}
/* linked list People to binary tree Family */
BinaryTreePtr convert_family(LinkedListPtr People){
	printf("  Converting . . . \n");
	char root[50];
	root[0] = '\0';
	strcpy(root, People->name);
	printf("  Root : %s\n", root);
	BinaryTreePtr Family = create_tree(People, root, 0);
	return Family;
}
/* writing DataFamily.csv */
void write_family(BinaryTreePtr Family){
	FILE *fp = fopen("DataFamily.csv", "w");
	
	if(fp == NULL){
		perror("  Unable to write DataFamily.csv ");
		return;
	}
	
	perror("  Writing to DataFamily.csv ");
	
	fprintf(fp, "NAME;FIRST CHILD;NEXT SIBLING;LEVEL\n");
	
	StackPtr stack = NULL;
	stack_push(&stack, Family);
	
	while(stack != NULL){
		BinaryTreePtr T = stack_pop(&stack);
		char child[30], sibling[30];
		// string init
		child	[0] = '\0';
		sibling	[0] = '\0';
		// add sibling
		if(T->sibling == NULL) strcpy(sibling, "NO_SIBLING");
		else{
			stack_push(&stack, T->sibling);
			strcpy(sibling, T->sibling->name);	
		}
		// add child
		if(T->child == NULL) strcpy(child, "NO_CHILD");
		else{
			stack_push(&stack, T->child);
			strcpy(child, T->child->name);
		}
		// add to file
		printf("  Writing . . . %-30s %-30s %-30s %-10d\n", T->name, child, sibling, T->level);
		fprintf(fp, "%s;%s;%s;%d\n", T->name, child, sibling, T->level);
	}
	perror("  Writing succesful to DataFamily.csv ");
	fclose(fp);
}
/* scan data of who in People */
LinkedListPtr scan_people(char* who){	
	FILE *fp = fopen("DataPeople.csv", "r");
	if(fp == NULL){
		perror("  Unable to read DataPeople.csv ");
		fclose(fp);
		return NULL;
	}
	else{
		printf("  Searching %s ... \n", who);
		char line[1024];
		int lineNo;
		for(lineNo = 0; fgets(line, sizeof(line), fp); lineNo++){
			char name[30], parent[30], gender[10], age[10], err[10];
			name	[0] = '\0';		//reset string to null
			parent	[0] = '\0';
			gender	[0] = '\0';
			age		[0] = '\0';
			err		[0] = '\0';
			
			int cek = sscanf(line, "%[^;];%[^;];%[^;];%[^;];%s", parent, name, gender, age, err);
			if(cek < 5){
				printf("  ... Format error in line %-3d ...\n", lineNo);
				continue;
			}
			if(!lineNo) continue;
			LinkedListPtr newPtr;
			newPtr = (LinkedListPtr) malloc(sizeof(LinkedList));
			if(newPtr != NULL){
				if(!(newPtr->name = (char*) malloc(sizeof(char) * (strlen(name)+1)))){
					perror("  Memory not allocated ");
				}
				Trim(name);
				Capitalize(name);
				strcpy(newPtr->name, name);
				
				newPtr->gender 	= Convert(gender);
				newPtr->age 	= Convert(age);
				
				if(!(newPtr->parent = (char*) malloc(sizeof(char) * (strlen(parent)+1)))){
					perror("  Memory not allocated ");
				}
				Trim(parent);
				Capitalize(parent);
				strcpy(newPtr->parent, parent);
				
				newPtr->next = NULL;
				
				if(strcmp(newPtr->name, who) == 0){
					return newPtr;
				}
			}
		}
	}
	fclose(fp);
	return NULL;
}
/* reading DataFamily.csv */
int scan_family(char* who){
	FILE *fp = fopen("DataFamily.csv", "r");
	
	if (fp == NULL){
		perror("  Unable to read DataFamily.csv ");
		return -1;
	}
	
	char line[1024];
	int lineNo;
	
	for(lineNo = 0; fgets(line, sizeof(line), fp); lineNo++){
		char name[50], child[50], sibling[50], level[50];
		// string init
		name	[0]	= '\0';
		child	[0] = '\0';
		sibling	[0] = '\0';
		level	[0]	= '\0';
		
		int cek = sscanf(line, "%[^;];%[^;];%[^;];%s", name, child, sibling, level);	
		
		if(!lineNo) continue;
		
		if(strcmp(who, name) == 0){
			return Convert(level);
		}
	}
	fclose(fp);
	return -1;
}
/* Display content of linked list */
void print_list(){
	FILE *fp = fopen("DataPeople.csv", "r");
	if(fp == NULL){
		perror("  Unable to read DataPeople.csv ");
	}
	else{
		printf("  %-30s %-30s %-10s %-10s\n", "PARENT", "NAME", "GENDER", "AGE");
		char line[1024];
		int lineNo;
		for(lineNo = 0; fgets(line, sizeof(line), fp); lineNo++){
			char name[30], parent[30], gender[10], age[10], err[10];
			name	[0] = '\0';		//reset string to null
			parent	[0] = '\0';
			gender	[0] = '\0';
			age		[0] = '\0';
			err		[0] = '\0';
			
			int cek = sscanf(line, "%[^;];%[^;];%[^;];%[^;];%s", parent, name, gender, age, err);
			if(!lineNo) continue;
			if(Convert(gender)) strcpy(gender, "MALE");
			else strcpy(gender, "FEMALE");
			printf("  %-30s %-30s %-10s %-10s\n", parent, name, gender, age);
		}
	}
	fclose(fp);
}
/* Display content of Binary Tree */
void print_tree(){
	FILE *fp = fopen("DataFamily.csv", "r");
	if(fp == NULL){
		perror("  Unable to read DataFamily.csv ");
	}
	else{
		char line[1024];
		while(fgets(line, sizeof(line), fp)){
			char name[30], fc[30], ns[10], level[10];
			name	[0] = '\0';		//reset string to null
			fc		[0] = '\0';
			ns		[0] = '\0';
			level	[0] = '\0';
			
			int cek = sscanf(line, "%[^;];%[^;];%[^;];%s", name, fc, ns, level);
			printf("  %-30s %-30s %-30s %-10s\n", name, fc, ns, level);
		}
	}
	fclose(fp);
}
