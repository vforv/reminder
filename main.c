/* 
 * File:   main.c
 * Author: root
 *
 * Created on June 26, 2015, 7:31 PM
 */

#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define RESET "\033[0m"

char createDatabaseIfNotExists();
/*
 * 
 */
int main(int argc, char** argv) {
    
    if(createDatabaseIfNotExists("database")){
        printf(KGRN "[+] " RESET "DATABSE FILE EXISTS\n");
        puts(KGRN "[+] " RESET "INITIALIZATION STARTED...\n");
        
    }else{
        printf(KRED "[-] " RESET "DATABASE FILE NOT EXISTS");
    }
    return (EXIT_SUCCESS);
}

char createDatabaseIfNotExists(char * filename){
    FILE * database;
    if(database = fopen(filename, "r")){
        fclose(database);
        return TRUE;
    }else{
        database = fopen(filename, "w");
        fprintf(database, "TEST");
        fclose(database);
        puts(KGRN "[+] " RESET "DATABASE FILE CREATED\n");
        puts(KGRN "[+] " RESET "INITIALIZATION STARTED...\n");
        return FALSE;
    }
}