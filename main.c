/* 
 * File:   main.c
 * Author: root
 *
 * Created on June 26, 2015, 7:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <pcre.h>
#include <string.h>
#include <time.h>

#define TRUE  1
#define FALSE 0

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define RESET "\033[0m"

char createDatabaseIfNotExists();
void readFileAndCreateTable();

/*
 * 
 */

//MAIN CODE
int main(int argc, char** argv) {

      
    if(createDatabaseIfNotExists("database")){
        printf(KGRN "[+] " RESET "DATABSE FILE EXISTS\n");
        puts(KGRN "[+] " RESET "INITIALIZATION STARTED...\n");
        readFileAndCreateTable();
        
    }else{
        printf(KRED "[-] " RESET "DATABASE FILE NOT EXISTS");
        readFileAndCreateTable();
    }
    
    
    return (EXIT_SUCCESS);
}

//DATABASE FUNCTION 
char createDatabaseIfNotExists(char * filename){
    FILE * database;
    if(database = fopen(filename, "r")){
        fclose(database);
        return TRUE;
    }else{
        database = fopen(filename, "w");
        fclose(database);
        puts(KGRN "[+] " RESET "DATABASE FILE CREATED\n");
        puts(KGRN "[+] " RESET "INITIALIZATION STARTED...\n");
        return FALSE;
    }
}

enum { MAXLINES = 300 };
    //READ FILE AND CREATE TABLE
void readFileAndCreateTable(){
        char lines[MAXLINES][BUFSIZ];
        int i = 0;
        
        FILE * database;
        database = fopen("database", "r" );
        while (i < MAXLINES && fgets(lines[i], sizeof(lines[0]), database))
            {
                lines[i][strlen(lines[i])-1] = '\0';
                i = i + 1;
            }
         
            fclose(database);
            
            int k;
            for(k = 0;k < i;k++){
            printf("%s \n", lines[k]); 
            }            
}
void returnCleanRow(char * cont){
        char* token;
        int br = 1;
        int i;
        char* tofree;
        char *string = strdup(cont);
        int broj = numberOfLines();
        char * list[8];

       
        if (string != NULL) {

          tofree = string;

          while ((token = strsep(&string, "|")) != NULL)
          {
              list[br] = token;
              br++;
          }
          
          
          
          free(tofree);
        }
        for(i = 1;i < 8 ;i++){
              printf("%s \n", list[i]);
          }
}



void generateArray(){
    
} 

void generateByDate(){
    
}

void generateTable(){
    
}
int numberOfLines(){
//         int broj;
//        FILE * database;
//        database = fopen("database", "r" );
//        char singleLine[150];
//        while(!feof(database)){
//            fgets(singleLine, 150, database);
//            broj++;
//        }
//        return broj;
//        fclose(database);
}
time_t to_seconds(const char *date)
{
        struct tm storage={0,0,0,0,0,0,0,0,0};
        char *p=NULL;
        time_t retval=0;

        p=(char *)strptime(date,"%d-%b-%Y",&storage);
        if(p==NULL)
        {
                retval=0;
        }
        else
        {
                retval=mktime(&storage);
        }
        return retval;
}
// char *date1="20-JUN-2006";
//   char *date2="21-JUN-2006";
//   time_t d1=to_seconds(date1);
//   time_t d2=to_seconds(date2);
//   
//   printf("date comparison: %s %s ",date1,date2);
//   if(d1==d2) printf("equal\n");
//   if(d2>d1)  printf("second date is later\n");
//   if(d2<d1)  printf("seocnd date is earlier\n");