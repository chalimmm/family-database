#include <windows.h>
#include <process.h>

void bar(int n);
void center();
void clear();
void pause();
void maximize();
void resize(int x, int y, int w, int h);

/* Window Adjust */
void resize(int x, int y, int w, int h){
	HWND hwnd = GetConsoleWindow();
	if( hwnd != NULL ){ MoveWindow(hwnd, x, y, w, h, TRUE); }
}
/* Minimize Screen to center*/
void center(){
	clear();
	resize(500, 100, 400, 400);
}
/* Maximize Screen */
void maximize(){
	clear();
	resize(100, 100, 1000, 600);
}
/* Clear Screen */
void clear(){
	system("cls");
}
/* Wait user input to continue */
void pause(){
	printf("  ");
	system("pause");
}
/* Print bar */
void bar(int n){
	int i;
	for(i=0; i<n; i++) printf("%c", 254);
	printf("\n");
}
