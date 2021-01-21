#include "file_csv.h"
#include "screen.h"

int  select_menu();
void welcome();
void main_menu();
void menu_exit();
void menu_howto();
void menu_view();
void menu_update();
void menu_find();
void what_relation(LinkedListPtr Person1, LinkedListPtr Person2);

void welcome(){
	center();
	printf("  										  \n");
	printf("   HELLO :) ");
	bar(30);
	printf("   _______________________________________\n");
	printf("                                          \n");
	printf("    FFFFF   AA   M   M  II  LL    Y   Y   \n");
	printf("    FF     A  A  MM MM  II  LL    Y   Y   \n");
	printf("    FFFF   AAAA  M M M  II  LL     YYY    \n");
	printf("    FF     A  A  M   M  II  LL      Y     \n");
	printf("    FF     A  A  M   M  II  LLLLL   Y     \n");
	printf("                                          \n");
	printf("   _____________ [WELCOME!] ______________\n");
	printf("                                          \n");
	printf("             Program Sederhana            \n");
	printf("        Database Silsilah Keluarga        \n");
	printf("                                          \n");
	printf("     Akbar Abdirahman       (1906381672)  \n");
	printf("     Chandra Halim Nuruddin (1906381584)  \n");
	printf("                                          \n");
	printf("  ");
	bar(40);
	pause();
}

int select_menu(){
	char select[100];
	InputString(select);
	return Convert(select);
}

void main_menu(){
	center();
	printf("  MENU ");
	bar(35);
	printf("  [0] EXIT                               \n");
	printf("  [1] HOW TO                             \n");
	printf("  [2] VIEW DATABASE                      \n");
	printf("  [3] UPDATE DATABASE                    \n");
	printf("  [4] FIND RELATIONSHIP                  \n");
	printf("  ");
	bar(40);
	printf("  SELECT: ");
	switch(select_menu()){
		case 0:{
			menu_exit();
			break;
		}
		case 1:{
			menu_howto();
			break;
		}
		case 2:{
			menu_view();
			break;
		}
		case 3:{
			menu_update();
			break;
		}
		case 4:{
			menu_find();
			break;
		}
		default:{
			perror("  Invalid format input ");
			pause();
			break;
		}
	}
	main_menu();
}

void menu_exit(){
	center();
	printf("  MENU > EXIT ");
	bar(28);
	printf("  ARE YOU SURE ?                         \n");
	printf("  [0] NO                                 \n");
	printf("  [1] YES                                \n");
	printf("  ");
	bar(40);
	printf("  SELECT: ");
	switch(select_menu()){
		case 0:{
			return;
			break;
		}
		case 1:{
			perror("  Exit program . . . ");
			exit(1);
			break;
		}
		default:{
			perror("  Invalid format input ");
			pause();
			break;
		}
	}
	menu_exit();
}

void menu_howto(){
	maximize();
	printf("  MENU > HOW TO ");
	bar(100);
	guidebook();
	printf("  ");
	bar(114);
	printf("  ");
	system("pause");
	main_menu();
}

void menu_view(){
	maximize();
	printf("  MENU > VIEW DATABASE > DataPeople.csv ");
	bar(77);
	print_list();
	printf("  ");
	bar(114);
	pause();
	
	maximize();
	printf("  MENU > VIEW DATABASE > DataFamily.csv ");
	bar(77);
	print_tree();
	printf("  ");
	bar(114);
	pause();
	main_menu();
}

void menu_update(){
	center();
	printf("  MENU > UPDATE ");
	bar(26);
	printf("  [0] BACK                               \n");
	printf("  [1] UPDATE                             \n");
	printf("  ");
	bar(40);
	printf("  SELECT: ");
	switch(select_menu()){
		case 0:{
			main_menu();
			break;
		}
		case 1:{
			maximize();
			printf("  MENU > UPDATE > DataPeople.csv ");
			bar(77);
			LinkedListPtr People = read_people();
			write_people(People);
			pause();
			maximize();
			printf("  MENU > UPDATE > DataFamily.csv ");
			bar(77);
			BinaryTreePtr Family = convert_family(People);
			write_family(Family);
			break;
		}
		default:{
			perror("  Invalid format input ");
			break;
		}
	}
	pause();
	main_menu();
}

void menu_find(){
	center();
	printf("  MENU > FIND RELATIONSHIP ");
	bar(15);
	printf("  [0] BACK                               \n");
	printf("  [1] ENTER NAME                         \n");
	printf("  ");
	bar(40);
	printf("  SELECT: ");
	switch(select_menu()){
		case 0:{
			main_menu();
			break;
		}
		case 1:{
			char name1[30], name2[30];
			printf("  ");
			bar(40);
			printf("  ENTER 1st NAME : ");
			InputString(name1);
			Capitalize(name1);
			printf("  1st NAME       : %-30s\n", name1);
			LinkedListPtr p1 = scan_people(name1);
			if(p1 == NULL){
				printf("  %s not found\n", name1);
				pause();
				menu_find();
			}
			else printf("  %s found\n", name1);
			printf("  ");
			bar(40);
			printf("  ENTER 2nd NAME : ");
			InputString(name2);
			Capitalize(name2);
			printf("  2nd NAME       : %-30s\n", name2);
			LinkedListPtr p2 = scan_people(name2);
			if(p2 == NULL){
				printf("  %s not found\n", name2);
				pause();
				menu_find();
			}
			else printf("  %s found\n", name2);
			bar(40);
			printf("  ");
			what_relation(p1, p2);
			break;
		}
	}
	pause();
	menu_find();
}

void what_relation(LinkedListPtr P1, LinkedListPtr P2){
	int level1 = scan_family(P1->name);
	int level2 = scan_family(P2->name);
	char s[15];
	s[0] = '\0';
	switch(level1-level2){
		case 0:{	// Same level: Sibling if same parent, else cousin
    		// Relation of name1 to name2
            strcpy(s,"sister");
            if(P1->gender) strcpy(s,"brother");
            if(strcmp(P1->parent, P2->parent) == 0)printf("%s is %s's %s\n", P1->name, P2->name, s);
            else printf("%s and %s are cousin\n", P1->name, P2->name);
			break;
		}
    	case 1:{	//Difference of level = 1 -> Child if immediate, else niece/nephew
            strcpy(s,"daughter");
            if(P1->gender) strcpy(s,"son");
            if(strcmp(P1->parent, P2->name) == 0) printf("%s is %s's %s\n", P1->name, P2->name, s);
            else{
				strcpy(s,"niece");
	            if(P1->gender) strcpy(s,"nephew");
	            printf("%s is %s's %s\n", P1->name, P2->name, s);
			}
			break;
		}
    	case -1:{ 	//Difference of level = -1 -> Parent if immediate, else uncle/aunt
            strcpy(s,"mother");
            if(P1->gender) strcpy(s,"father");
            if(strcmp(P1->name, P2->parent) == 0) printf("%s is %s's %s\n", P1->name, P2->name, s);
            else{
            	strcpy(s,"aunt");
	            if(P1->gender) strcpy(s,"uncle");
	            printf("%s is %s's %s\n", P1->name, P2->name, s);
			}	
            break;
		}
    	case 2:{	// Difference oh level = 2 -> Grand child if same link
            strcpy(s,"daughter");
            if(P1->gender) strcpy(s,"son");
            printf("%s is grand %s of %s\n", P1->name, s, P2->name);
			break;
		}
    	case -2:{	// Difference oh level = -2 -> Grand parents if same link
            strcpy(s,"mother");
            if(P1->gender) strcpy(s,"father");
            printf("%s is grand %s of %s\n", P1->name, s, P2->name);
			break;
		}
    	default:
            perror("Too far relationship\n");
            break;
	}
}
