/*
** Password-cracker Latest Version: Friday 29-5-19 7:50pm Panagiotis (Peter) Goulas - Commputer Systems - Project 2
// Version: working version of arg2 30-5-19 11:49
*/ 

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.c"
#include "sha256.h"
#include <sys/stat.h>
#include <ctype.h>

#define ASCII_LOWER 32
#define ASCII_UPPER 126
#define MAX_ROWS    10
#define MAX_COLS    32
#define MAX_CHARS   320
#define MAX_ARRAY   10000


/* temporary global variables */
int saved_chars[MAX_ROWS][MAX_COLS];
int saved_chars2[20][32];
unsigned char chars[MAX_CHARS];
unsigned char chars2[640];
// unsigned char chars3[320000]; // assume 10 000 passwords
BYTE string1[4];
BYTE string2[6];


/* function prototypes */
void save_progress(int row, int col, int count);
void save_string1(int i, int j, int k, int m);
void cut_off_last(char array_to_print, SHA256_CTX ctx);
int check_equality(int row, int col, BYTE buffer[SHA256_BLOCK_SIZE]);
int check_equality2(int row, int col, BYTE buffer2[SHA256_BLOCK_SIZE]);
void save_progress2(int row2, int col2, int count2);
// void save_progress3(int row2, int col2, int count2);
void save_string2(int i, int j, int k, int m, int f, int g);
long int findSize(const char *file_name);
int print_common_password(char common_password[46], int count, int passwords_number);
//void numbers_variation(char common_password[46],int count, int passwords_number);
int letters_bruteforce(int count, int passwords_number);
int increase_by_1(int count);






int main(int argc, char * argv[])
{   
    /* used the following link for the code below */
    /* https://github.com/B-Con/crypto-algorithms/blob/master/sha256_test.c */
    BYTE buffer[SHA256_BLOCK_SIZE];
    BYTE buffer2[SHA256_BLOCK_SIZE];
    BYTE buffer3[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;

    int i = 0, j = 0, k = 0, m = 0, count = 0;
    int row = 0, col = 0, char_count = 0, count_times = 0;
    int col2 = 0, row2 = 0, char_count2=0, count2 = 0, f = 0, g = 0;

    /* used code from the following tutorial: */ 
    /* https://stackoverflow.com/questions/17598572/read-write-to-binary-files-in-c */
    FILE *ptr;
    ptr = fopen("pwd4sha256","rb"); // r for read b for binary
    // fread(chars,sizeof(chars),1,ptr);

    size_t a = fread(chars,sizeof(chars),1,ptr);

    if (count2 == 5){
        printf("a=%ld", a);
    }

    /* iterate and save */
    while (count < 320) {
        if (char_count == 32) {
            /* reset col to 0  and change row */
            col = 0;
            char_count = 0;
            row = increase_by_1(row);
        }
        save_progress(row, col, count);

        col = increase_by_1(col);
        count = increase_by_1(count);
        char_count = increase_by_1(char_count);
        
    }


    // file 2

    /* used code from the following tutorial: */ 
    /* https://stackoverflow.com/questions/17598572/read-write-to-binary-files-in-c */
    FILE *ptr2;
    ptr2 = fopen("pwd6sha256","rb"); // r for read b for binary
   
    size_t b = fread(chars2,sizeof(chars2),1,ptr2);

    if (count2 == 5){
        printf("a=%ld", b);
    }


    while (count2< 640) {
        if (char_count2 == 32) {
            /* reset col to 0  and change row */
            col2 = 0;
            char_count2 = 0;
            row2 = increase_by_1(row2);
        }
        save_progress2(row2, col2, count2);
        col2 = increase_by_1(col2);
        count2 = increase_by_1(count2);
        char_count2 = increase_by_1(char_count2);
    }

    /* used only with 0 arguments to find 4 and 6 char passwords */
    if (argc == 1) {

        /* 4 char passwords */
        i = ASCII_LOWER;
        j = ASCII_LOWER;
        k = ASCII_LOWER;
        m = ASCII_LOWER;
        row = 0;
        col = 0;
        for (i=ASCII_LOWER; i<=ASCII_UPPER; i++){
            for (j=ASCII_LOWER; j<=ASCII_UPPER; j++){
                for (k=ASCII_LOWER; k<=ASCII_UPPER; k++){
                    for (m=ASCII_LOWER; m<=ASCII_UPPER; m++){
                        save_string1(i, j, k, m);

                        /* used the following link for the code below */
                        /* https://github.com/B-Con/crypto-algorithms/blob/master/sha256_test.c */
                        sha256_init(&ctx);
                        sha256_update(&ctx, string1, sizeof(string1));
                        sha256_final(&ctx, buffer);

                        for (row = 0; row < MAX_ROWS; row++) {
                            count_times = 0;
                            for (col = 0; col < MAX_COLS; col++) {

                                /* check if chars and saved_chars char is same */
                                if (check_equality(row,col,buffer)) {
                                    count_times +=1;
                                }
                                if (count_times == MAX_COLS){
                                    //print_out(ctx, row);
                                    printf("%s %d\n", string1, (row+1));


                                }
                            }
                        }
                    }
                }
            }
        }
    

    /* 6 char passwords */

        i = ASCII_LOWER;
        j = ASCII_LOWER;
        k = ASCII_LOWER;
        m = ASCII_LOWER;
        f = ASCII_LOWER;
        g = ASCII_LOWER;

        row = 0;
        col = 0;
        count_times = 0;
        for (i=ASCII_LOWER; i<=ASCII_UPPER; i++){
            for (j=ASCII_LOWER; j<=ASCII_UPPER; j++){
                for (k=ASCII_LOWER; k<=ASCII_UPPER; k++){
                    for (m=ASCII_LOWER; m<=ASCII_UPPER; m++){
                        for (f=ASCII_LOWER; f<=ASCII_UPPER; f++){
                            for (g=ASCII_LOWER; g<=ASCII_UPPER; g++){

                                save_string2(i, j, k, m, f, g);

                                /* used the following link for the code below */
                                /* https://github.com/B-Con/crypto-algorithms/blob/master/sha256_test.c */
                                sha256_init(&ctx);
                                sha256_update(&ctx, string2, sizeof(string2));
                                sha256_final(&ctx, buffer2);

                                for (row = 0; row < MAX_ROWS; row++) {
                                    count_times = 0;
                                    for (col = 0; col < MAX_COLS; col++) {

                                        /* check if chars and saved_chars char is same */
                                        if (check_equality2(row,col,buffer2)) {
                                            count_times +=1;
                                        }
                                        if (count_times == MAX_COLS){
                                            //print_out(ctx, row);
                                            printf("%s %d\n", string2, (row+1));

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
   if (argc == 3) {
        // file 3

        /* used code from the following tutorial: */ 
        /* https://stackoverflow.com/questions/17598572/read-write-to-binary-files-in-c */
        FILE *ptr3;
        ptr3 = fopen(argv[2] ,"rb"); // r for read

        // get the size with these 2 lines 
        // fseek(ptr3, 0L, SEEK_END);
        // long int sz = ftell(ptr3);

        // https://www.includehelp.com/c-programs/find-size-of-file.aspx
        long int sz;
        sz = findSize(argv[2]);

        //printf("\n\n this is sz=%d\n\n", sz);    // success!!

        unsigned char chars3[sz+1];

        // unsigned char chars3[320];

        // fread(chars3,sizeof(chars3),1,ptr3);


        size_t c = fread(chars3,sizeof(chars3),1,ptr3);

        if (count2 == 5){
            printf("a=%ld", c);
        }

        count2 = 0;
        char_count2 = 0;
        col2 = 0;
        row2 = 0;
        int new_int = 0;

        // new_int2 = (sz) * 32; // not used

        new_int = (sz)/32;

        // printf("\n\n this is new_int=%d\n\n", new_int); // correct

        // // new_int = 10;  // a good alternative not used currently

        int saved_chars3[new_int][32];
        



        while (count2< sz) {              // gets affected with seg fault when new_int2
            if (char_count2 == 32) {
                /* reset col to 0  and change row */
                col2 = 0;
                char_count2 = 0;
                row2 = increase_by_1(row2);
            }
            // save_progress2(row2, col2, count2);
            saved_chars3[row2][col2] = chars3[count2];

            col2 = increase_by_1(col2);
            count2 = increase_by_1(count2);
            char_count2 = increase_by_1(char_count2);
        }

        // should work up to here -> test seg fault --> was not specifying the file in the arg
        // not printing correctly, not printing with sz
        // print array

        FILE *ptr4;
        ptr4 = fopen(argv[1], "r");
        
        char my_lovely_array[MAX_ARRAY];
        while( fscanf(ptr4, "%s", my_lovely_array) != EOF ){
            //printf("\n%s\n", my_lovely_array);   // success


            sha256_init(&ctx);
            sha256_update(&ctx, (BYTE*)my_lovely_array, strlen(my_lovely_array));
            sha256_final(&ctx, buffer3);

            for (row2 = 0; row2 < new_int; row2++) {
                count_times = 0;
                
                for (col2 = 0; col2 < MAX_COLS; col2++) {

                    //check if chars and saved_chars char is same 
                    
                    if (saved_chars3[row2][col2] == buffer3[col2]) {
                        
                        count_times++;
                    }
                    
                    if (count_times == 32){
                        printf("%s %d\n", my_lovely_array, (row2+1));
                    }

                    
                }
            }
        }
    }



    if (argc == 2) {
    
        FILE *ptr5;
        ptr5 = fopen("passwords_list.txt" ,"r");
        FILE *ptr6;
        ptr6 = fopen("passwords_list.txt" ,"r");

        // https://www.cs.swarthmore.edu/~newhall/unixhelp/C_commandlineargs.php
        // get the number from the command line
        int passwords_number = atoi(argv[1]);

        char common_password[46];
        //char common_password2[46];
        char original_password[46];

        count = 0;
        //count2 = 0;

        // int word_size = 0;

        // print all the words once - includes 6 letter passwords of actors, 
        // political leaders favorite singers, found passwords of classmates etc
        while( fscanf(ptr6, "%s", common_password) != EOF ){
            if (count >= passwords_number) {
                break;
            }
            count = print_common_password(common_password, count, passwords_number); 

        }

        // print variations of the above list -> first capital letter, last capital 
        // all capitals 
        while( fscanf(ptr5, "%s", common_password) != EOF ){
            if (count >= passwords_number) {
                break;
            }
            //word_size = strlen(common_password);
            // if (word_size == 6) {

            // copy to have the original str
            strcpy(original_password, common_password);

            //printf("\n%s\n", common_password);

            //count = print_common_password(common_password, count, passwords_number);   

            //printf("\nword_size=%d\n", word_size);
            //printf("\nword number=%d\n", count);
            //count++;
            //printf("\n%d\n", count);

            common_password[0] = toupper(common_password[0]);

            //printf("\n%s\n", common_password);
            count = print_common_password(common_password, count, passwords_number);      
            //printf("\n%d\n", count);
            //printf("\nword number=%d\n", count);
            //count++;

            // make last letter capital
            strcpy(common_password, original_password);
            common_password[5] = toupper(common_password[5]);
            // printf("\n%d\n", count);
            //printf("\n%s\n", common_password);    

            //printf("\nword number=%d\n", count);
            //count++;

            count = print_common_password(common_password, count, passwords_number);   



            // make all capitals
            strcpy(common_password, original_password);
            common_password[0] = toupper(common_password[0]);
            common_password[1] = toupper(common_password[1]);
            common_password[2] = toupper(common_password[2]);
            common_password[3] = toupper(common_password[3]);
            common_password[4] = toupper(common_password[4]);
            common_password[5] = toupper(common_password[5]);

            //printf("\n%s\n", common_password);   

            //printf("\nword number=%d\n", count);
            //count++;


            count = print_common_password(common_password, count, passwords_number); 


            //printf("\n%d\n", count);
            strcpy(common_password, original_password);
            // numbers_variation(common_password, count, passwords_number);
            // for (i=0; i<=9; i++){
            //     common_password[0] = (char)i;
            //     print_common_password(common_password, count, passwords_number);
            // }

            if (count >= passwords_number) {
                break;
            }

        }

        // need more passwords? no problem bruteforce is here
        if (count < passwords_number) {
            count = letters_bruteforce(count, passwords_number);
        }
        // printf("\nthis is the passwords_number=%d\n", passwords_number);
        fclose(ptr5);
        fclose(ptr6);
    }
    
    return 0;
}

int letters_bruteforce(int count, int passwords_number){
    char string1[45];
    int i=0, j=0, k=0, m=0, f= 0, g = 0;
    for (i = 32; i<=126; i++){
        for (j = 32; j<=126; j++){
            for (k = 32; k<=126; k++){
                for (m = 32; m<=126; m++){
                    for (f = 32; f<=126; f++){
                        for (g = 32; g<=126; g++){
                            string1[0] = i;
                            string1[1] = j;
                            string1[2] = k;
                            string1[3] = m;
                            string1[4] = f;
                            string1[5] = g;
                            string1[6] = '\0';

                            // count2 ++;
                            // printf("\nstring=%s\n", string1);
                            // printf("\nstring[0]=%c\n", string1[0]);
                            // printf("\nstring[1]=%c\n", string1[1]);
                            // printf("\nstring[2]=%c\n", string1[2]);
                            // printf("\nstring[3]=%c\n", string1[3]);
                            // printf("\ncount=%d\n", count2);

                            if (count < passwords_number) {
                                printf("%s\n", string1);
                                count++;
                                //printf("\ncount=%d\n", count);
                            }

                            if (count>= passwords_number){
                                return count;
                            }
                        }
                    }
                }
            }
        }
    }

    return count;
}

// void numbers_variation(char common_password[46],int count, int passwords_number) {
//     int i = 0;
//     for (i=0; i<=9; i++){
//         common_password[0] = (char)i;
//         print_common_password(common_password, count, passwords_number);
//     }
// }

int print_common_password(char common_password[46], int count,int passwords_number) {
    if (count < passwords_number) {
        printf("%s\n", common_password);
        count++;
        //printf("\ncount=%d\n", count);
    }
    return count;
}

int check_equality(int row, int col, BYTE buffer[SHA256_BLOCK_SIZE]) {
    if (saved_chars[row][col] == buffer[col]) {
        return 1;
    } else {
        return 0;
    }
}

int check_equality2(int row2, int col2, BYTE buffer2[SHA256_BLOCK_SIZE]) {
    if (saved_chars2[row2][col2] == buffer2[col2]) {
        return 1;
    } else {
        return 0;
    }
}

void save_string1(int i, int j, int k, int m){
    string1[0] = i;
    string1[1] = j;
    string1[2] = k;
    string1[3] = m;
}

void save_string2(int i, int j, int k, int m, int f, int g){
    string2[0] = i;
    string2[1] = j;
    string2[2] = k;
    string2[3] = m;
    string2[4] = f;
    string2[5] = g;
}

void save_progress(int row, int col, int count) {
    saved_chars[row][col] = chars[count];
}

void save_progress2(int row2, int col2, int count2) {
    saved_chars2[row2][col2] = chars2[count2];
}

// void save_progress3(int row2, int col2, int count2) {
//     saved_chars3[row2][col2] = chars3[count2];
// }

// function to get size of the file
// https://www.includehelp.com/c-programs/find-size-of-file.aspx
long int findSize(const char *file_name)
{
    struct stat st; /*declare stat variable*/
     
    /*get the size using stat()*/
     
    if(stat(file_name,&st)==0)
        return (st.st_size);
    else
        return -1;
}

int increase_by_1(int count) {
    count = count + 1;
    return count;
}
