#include "define.h"

void Capitalize(char *str);
int  Compare(char *str1, char *str2);
int	 Convert(char *str);
void Copy(char *str1, char *str2);
void InputString(char *str);
void Trim(char *str);

/* Input String
 * String akan dibaca menggunakan gets
 * Kemudian, string akan diedit formatnya menggunakan Trim
 */
void InputString(char *str){
	scanf("%[^\n]%*c", str);
	Trim(str);
}
/* Menghapus kelebihan spasi pada string str
 * 1 parameter string yang akan diubah -> str
 * menggunakan temporary string -> tmp
 * looping dengan 2 iterator yang berbeda untuk masing-masing string
 * hasil string di tmp dikembalikan ke str dengan strcpy
 */
void Trim(char *str){
	char *tmp;
	tmp = (char*) malloc(strlen(str)*sizeof(char));		//panjang string tmp = panjang string str
	if(tmp == NULL){
		printf("Error! memory not allocated.");
		exit(0);
	}
	int i = 0;											//i merupakan iterator untuk string asal
	int j = 0;											//j merupakan iterator untuk string baru
	while(str[i] != '\0'){								//jika bukan end of string
    	if(str[i] == ' ' || str[i] == '\t'){			
    		if(i > 0) tmp[j] = ' ', j++;				//jika bukan leading space maka tambahkan 1 space
    		while(str[i] == ' ' || str[i] == '\t') i++;	//skip untuk setiap kelebihan space
		}
		else tmp[j] = str[i], i++, j++;					//jika bukan space tambah saja ke string
	}
	strcpy(str, tmp);									//copy string yang sudah diubah ke string awal
	free(tmp);											//reset string tmp
	str[j] = '\0';										//end of string
}
/* Capitalize Each Word
 * Cek tiap karakter, untuk karakter pertama di tiap kata diubah menjadi huruf kapitalnya sisanya menjadi huruf kecil.
 */
void Capitalize(char *str){
	int len = strlen(str); 					//strlen: fungsi untuk mencari panjang string (banyak karakter) dari str
	int i;
	for(i=0; i<len; i++){ 					//looping tiap karakter
		if(str[i] >= 'a' && str[i] <= 'z')	//mengubah menjadi huruf kapital
			str[i] = str[i] - 32;
	}
}
/* String to Number Converter
 * Cek tiap karakter, jika dia angka maka bentuk bilangan, jika bukan maka return -1 (bukan angka)
 */
int Convert(char *str){
	int num = 0;						//num menyimpan bilangan hasil konversi
	int ten = 1;						//ten menyimpan pangkat dari 10 untuk menentukan posisi bilangan
	int len = strlen(str); 				//strlen -> fungsi untuk mencari panjang string (banyak karakter) dari str
	if(len>2) return -1; 				//jika panjang string > 2 berarti tidak mungkin nilai hasil konversi <= 20
	int i;
	for(i=len-1; i>=0; i--){ 			//looping dari end of string untuk membentuk bilangan
		if(str[i]>='0' && str[i]<='9'){ //jika karakter adalah angka
			num += ten*(str[i]-'0'); 	//bentuk bilangan dengan mengalikan karakter dengan ten
			ten *= 10; 					//nilai ten sama dengan 10^(len-i-1)
		}
		else return -1; 				//jika karakter bukan angka return -1
	}
	return num;							//return bilangan hasil konversi
}
