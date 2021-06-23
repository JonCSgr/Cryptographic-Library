#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>


#include "hy457_crypto.h"






int main()
{
    FILE* input;
    FILE* outputEncrypted;
    FILE* key;
    int d;
    int x;
    printf("Create test.txt for the plain text \n");
    printf("Create key.txt for the key on playfair\n");
    printf("For N key on Ceasar put it on  line 288(Encrypt) and 296(Decrypt) as a parameter to the function\n");
    
    printf("Choose an option Option: \n");
    printf("1: Caesar Encrypt\n");
    printf("2: Caesar Decrypt\n");
    printf("3: Affine Encrypt\n");
    printf("4: Affine Decrypt\n");
    printf("5: Playfair Encrypt\n");
    printf("6: Playfair Decrypt\n");
    printf("7: otp_encrypt Encrypt\n");
    printf("8: otp_encrypt Decrypt\n");

    printf("Choose a number\n");
    scanf("%d", &d);
        
    
     switch(d)
    {
        case 1:
          
            input = fopen("test.txt", "r");
            if(input == NULL) 
            printf("error");           
            printf("Choose a number for encryption Ceazar N= \n");
            scanf("%d", &x);
            caesar_encrypt(input, x);
            printf("Encrypted Succefully\n");
            break;

        case 2:
      
        outputEncrypted = fopen("outputEncrypted.txt", "r");
        if(outputEncrypted == NULL) 
        printf("error");
         printf("Choose a number for Decryption Ceazar N= \n");
             scanf("%d", &x);
        caesar_decrypt(outputEncrypted, x);
          printf("Decrypted Succefully\n");
        break;

        case 3:
            input = fopen("test.txt", "r");
            if(input == NULL) 
            printf("error");   
            affine_encrypt(input);
              printf("Encrypted Succefully\n");
            break;

        case 4:
        outputEncrypted = fopen("outputEncrypted.txt", "r");
        if(outputEncrypted == NULL) 
        printf("error");
        affine_decrypt(outputEncrypted);
          printf("Decrypted Succefully\n");
        break;

        case 5:
         input = fopen("test.txt", "r");
         if(input == NULL) 
         printf("error");
        key = fopen("key.txt","r");
        if (key == NULL)
        printf("error");
        char matrix[5][5];
        playfair_keymatrix(key,matrix);
    printf("Printing the matrix \n");
    for(int i=0; i<5; i++){
       for(int a=0;a<5;a++){
          printf("MatriX[%d][%d] = %c\n",i,a, matrix[i][a]);
        }   
      }
     playfair_encrypt(input,matrix);
       printf("Encrypted Succefully\n");
        break;
        
     
        case 6:
           input = fopen("outputEncrypted.txt", "r");
         if(input == NULL) 
         printf("error");
        key = fopen("key.txt","r");
        if (key == NULL)
        printf("error");
        char matrix2[5][5];
        playfair_keymatrix(key,matrix2);
    printf("Printing the matrix \n");
    for(int i=0; i<5; i++){
       for(int a=0;a<5;a++){
          printf("MatriX[%d][%d] = %c\n",i,a, matrix2[i][a]);
        }   
      }
     playfair_decrypt(input,matrix2);
      printf("Decrypted Succefully\n");
        break;
  
		case 7:
            input = fopen("test.txt", "r");
			int length;
            if(input == NULL) 
            printf("error");   
           length = countChars(input);
			generateKey(length);
			input = fopen("test.txt", "r");
			key = fopen("generatedKey.txt","r");
			otp_encrypt(input,key);
            printf("Encrypted Succefully\n");
            break;
		
			case 8:
            outputEncrypted = fopen("outputEncrypted.txt", "r");
			if(outputEncrypted == NULL) {
				printf("error");
				}
			key = fopen("generatedKey.txt","r");
			otp_decrypt(outputEncrypted,key);
            printf("Decrypted Succefully\n");
            break;
  
        default:
        printf("Error! choose a crypto argument");
    }
    
   // input = fopen("test.txt", "r");
  //  if(input == NULL) {
  //      printf("error");
   // }
    // caesar_encrypt(input, 4141);
   // affine_encrypt(input);
    
    
   // outputEncrypted = fopen("outputEncrypted.txt", "r");
   // if(outputEncrypted == NULL) {
   //     printf("error");
   // }
    // caesar_decrypt(outputEncrypted, 4141);
   //affine_decrypt(outputEncrypted);
   /*
    key = fopen("key.txt","r");
    if (key == NULL){
        printf("error");
        return 0;
    }
    char matrix[5][5];
    playfair_keymatrix(key,matrix);

    for(int i=0; i<5; i++){
       for(int a=0;a<5;a++){
          printf("MatriX[%d][%d] = %c\n",i,a, matrix[i][a]);
        }   
   }
 playfair_encrypt(input,matrix);
 
     */
   
    return 0;
}
