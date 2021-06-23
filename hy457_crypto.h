#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>


uint8_t* caesar_encrypt(FILE* plaintext, int N)
{

    FILE* outputEncrypted;
    outputEncrypted = fopen("outputEncrypted.txt", "w");

    char ch;
    while((ch = fgetc(plaintext)) != EOF) {

        for(int i = 0; i < N; i++) {
            ch = ch + 1;
            if(ch == 58) {
                ch = 65;
            } else if(ch == 91) {
                ch = 97;
            } else if(ch == 123) {
                ch = 48;
            }
        }
        fputc(ch, outputEncrypted);
    }
    fclose(plaintext);
    fclose(outputEncrypted);
    return 0;
}

uint8_t* caesar_decrypt(FILE* ciphertext, int N)
{
    FILE* outputDecrypted;
    outputDecrypted = fopen("outputDecrypted.txt", "w");

    char ch;
    while((ch = fgetc(ciphertext)) != EOF) {
        for(int i = 0; i < N; i++) {
            ch = ch - 1;
            if(ch == 47) {
                ch = 122;
            } else if(ch == 64) {
                ch = 57;
            } else if(ch == 96) {
                ch = 90;
            }
        }
        fputc(ch, outputDecrypted);
    }
    fclose(ciphertext);
    fclose(outputDecrypted);
    return 0;
}

//Sto x afairw 65 giati emeis theloume na antistxisoume to A-Z sto 0-20kati
//Alla an to skefteis an apo to 65 poy einai to A kaneis A-65=0, B-65=1, ETC 
//opote ginete i anistixia aytomata , kai meta prepei na kanw + 65 oste na mporo
//na grapso to sosto arithmo
uint8_t* affine_encrypt(FILE* plaintext)
{
    FILE* outputEncrypted;
    outputEncrypted = fopen("outputEncrypted.txt", "w");

    char ch;
    int a=11,b=19,m=26,x;
    while((ch = fgetc(plaintext)) != EOF) {
        ch = toupper(ch);
        x = ch - 65;
        ch = (a*x+b)%m;
        ch = ch + 65;
        fputc(ch, outputEncrypted);
    }
    fclose(plaintext);
    fclose(outputEncrypted);
    return 0;
}

int modular_multiplicative(){
    
   for (int i = 0; i < 26; i++) 
    { 
     if( ((11 * i) % 26) == 1){
         return i;
     }
    }  
    return 0;
}
//ipologizw tin modular 
//
uint8_t * affine_decrypt(FILE *ciphertext){
    FILE* outputDecrypted;
    outputDecrypted = fopen("outputDecrypted.txt", "w");

    char ch;
    int a=modular_multiplicative(),m=26;
    while((ch = fgetc(ciphertext)) != EOF) {
        
        ch = a * ((ch+65) - 19)%m;
        ch = ch + 65;
        fputc(ch, outputDecrypted);
    }
    fclose(ciphertext);
    fclose(outputDecrypted);
    return 0;
}

bool exist(char array[],char letter){
      
   for(int i = 0 ; i < strlen(array); i++){
        
         if(array[i] == letter){
             return false;
         }
         
        
    }
    return true;
    
    
}
void playfair_keymatrix(FILE *key,char matrix[5][5]){
 char ch; 
 char keyword[26]; //here we will save our first matrix letters.
 int i =0;
 while((ch = fgetc(key)) != EOF) {
      if(ch == 'J')
      {
         ch = 'I';   
      }
        
     if(i==0) //gt an valoyme mia if ti proti fora tha pesei se aternono vroxo i while sto exist afoy o pinakas einai adios
    { 
         keyword[i] = ch;
         i++;
         
    }else if(exist(keyword,ch))
     {
         keyword[i] = ch;
           i++;
     }    
}
    keyword[i]= '\0';
 fclose(key);

  int j='A';
  int temp ;
  while(j <= 'Z'){
      temp = j;
      if(temp == 'J')
          temp = 'I';
      if(exist(keyword,temp)){
          keyword[i] = temp;
          i++;
      }
      j++;
  }
  
   //adding null termnating string 
   keyword[i]= '\0';
  //here we will create the matrix 
  int z=0;
 // char matrix[5][5];
   for(int i=0; i<5; i++){
       for(int a=0;a<5;a++){
           matrix[i][a] = keyword[z];
           z++;
        }   
   }
   for(int i=0; i<5; i++){
       for(int a=0;a<5;a++){
          printf("Matrix[%d][%d] = %c\n",i,a, matrix[i][a]);
        }   
   }
 
}

void search(char letter1,char letter2,char matrix[5][5],int positions[4]){
    if(letter1 == 'J') letter1 = 'I';
    if(letter2 == 'J') letter2 = 'I';
 
    for(int i = 0; i <5; i++){
        for(int j=0;j<5;j++){
            if(letter1 == matrix[i][j]){
                positions[0] = i;
                positions[1] = j;
            }
            if(letter2 == matrix[i][j]){
                positions[2] = i;
                positions[3] = j;
            }
        }
    }
    
   
    
}

//gia to onetime pad ipologizw posous 
//xaraktires einai to input oste na mporo
//meta na kanw xor me N=IDIOUS XARAKTIRES.
int countChars(FILE *plaintext){
	
    char ch;
    int length = -1;
    while((ch = fgetc(plaintext)) != EOF) {
       length++;
    }
    fclose(plaintext);	
	return length;
}

void generateKey(int length){
	 FILE* generatedKey;
	 int i;
     generatedKey = fopen("generatedKey.txt", "w");
	 
	  unsigned char buffer[length];
	  int fd = open("/dev/urandom", O_RDONLY);
       read(fd, buffer, length);
	   close(fd);	
	   printf("Generated Key from /dev/urandom is :");
	   for(i = 0; i < sizeof(buffer); ++i){
	     fputc(( (char)(buffer[i])), generatedKey);
		 printf("%02X",(char)(buffer[i]),generatedKey);
	   }
	   printf("\n");
       fclose(generatedKey);	

}


uint8_t * otp_encrypt(FILE *plaintext,FILE* key){  
	 FILE* outputEncrypted;
    outputEncrypted = fopen("outputEncrypted.txt", "w");
	   char ch;
	   char chKey;
	while((ch = fgetc(plaintext)) != EOF) {
         chKey = fgetc(key);
        fputc(chKey^ch, outputEncrypted);
    }
    fclose(outputEncrypted);
    fclose(plaintext);
	fclose(key);
  
	return 0;
}

uint8_t * otp_decrypt(FILE *ciphertext,FILE* key){  
	 FILE* outputDecrypted;
     outputDecrypted = fopen("outputDecrypted.txt", "w");
	   char ch;
	   char chKey;
	while((ch = fgetc(ciphertext)) != EOF) {
         chKey = fgetc(key);
        fputc(chKey^ch, outputDecrypted);
    }
    fclose(outputDecrypted);
    fclose(ciphertext);
	fclose(key);
  
	return 0;
}
unsigned char* playfair_encrypt(FILE* plaintext,char matrix[5][5]){
     FILE* outputEncrypted;
     outputEncrypted = fopen("outputEncrypted.txt", "a");
  

    int positions[4];
    char ch,letter1,letter2;
    int isEven = 0;
    
    while((ch = fgetc(plaintext)) != EOF) {
        isEven++;
        
        letter1 = ch;
        ch = fgetc(plaintext);
        
        if(ch == letter1)
        {
            letter2 = 'X';
        }
        else
        {
        letter2 = ch ;
        }
        
        if(ch == EOF && isEven%2 != 0){
        letter2 = 'X';
        }else{
            isEven++;
        }
    
      search(letter1,letter2,matrix,positions);
       
        // positions[0] = letter1_row , positions[1] = letter1_column , 
        // positions[2] = letter2_row , positions[3] = letter2_column
        //to mod to vazoume gt an to position[] = 4 , exei tin timi 4 tote +1 gia to epomeno mod 5 paei sto 0
        
        //letter1_row == letter2_row = rule same row.
        if(positions[0] == positions[2]){
          fputc(matrix[positions[0]][(positions[1]+1)%5], outputEncrypted); 
          fputc(matrix[positions[2]][(positions[3]+1)%5], outputEncrypted);
        }else if (positions[1] == positions[3]){
          fputc(matrix[(positions[0]+1)%5][positions[1]],outputEncrypted); //e.g 01 kai 31 same column 1==1 , kai 0+1=1 kai 3+1 =4 opote piga apo katw 
          fputc(matrix[(positions[2]+1)%5][positions[3]],outputEncrypted); 
        }else{
          fputc(matrix[positions[0]][positions[3]],outputEncrypted);
          fputc(matrix[positions[2]][positions[1]],outputEncrypted);
        }
 
 
 }

  
    fclose(plaintext);
    fclose(outputEncrypted);
    return 0;
}

unsigned char* playfair_decrypt(FILE* ciphertext,char matrix2[5][5]){
    int positions2[4];
    char ch,letter1,letter2 ;
    FILE* outputDecrypted;
    outputDecrypted = fopen("outputDecrypted.txt", "a");
    
    
    while((ch = fgetc(ciphertext)) != EOF) {
        letter1 = ch;
        ch = fgetc(ciphertext);
        letter2 = ch;
        
     search(letter1,letter2,matrix2,positions2);
    
     if(positions2[0] == positions2[2]){
         positions2[1] = (positions2[1]-1)%5;
         if(positions2[1] < 0 ){
             positions2[1] = 5 + positions2[1];
         }
         positions2[3] = (positions2[3]-1)%5;
         if(positions2[3] < 0){
             positions2[3] = positions2[3] +5 ; 
         }
          fputc(matrix2[positions2[0]][positions2[1]], outputDecrypted); 
          fputc(matrix2[positions2[2]][positions2[3]], outputDecrypted);
        }else if (positions2[1] == positions2[3]){
            
         positions2[0] = (positions2[0]-1)%5;
         if(positions2[0] < 0 ){
             positions2[0] = 5 + positions2[0];
         }
         positions2[2] = (positions2[2]-1)%5;
         if(positions2[2] < 0){
             positions2[2] = positions2[2] +5 ; 
         }
            
            
          fputc(matrix2[positions2[0]][positions2[1]],outputDecrypted); 
          fputc(matrix2[positions2[2]][positions2[3]],outputDecrypted); 
        }else{
          fputc(matrix2[positions2[0]][positions2[3]],outputDecrypted);
          fputc(matrix2[positions2[2]][positions2[1]],outputDecrypted);
        }
    }
    
    fclose(ciphertext);
    fclose(outputDecrypted);
    return 0;
    
}
