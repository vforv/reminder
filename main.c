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
time_t to_seconds(const char *date);
void returnCleanRow(char * cont);
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

//READING
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
            
            char *date1;
            char *date2;
           while(1){
               int change = 0;
            for(k = 0;k < i;k++){
                char *string = strdup(lines[k]);
                char *string1 = strdup(lines[k + 1]);
                date1 = strsep(&string, "|");
                date2 = strsep(&string1, "|");
                    time_t d1=to_seconds(date1);
                    time_t d2=to_seconds(date2);
                    if(d1 > d2){
                        char tmp[BUFSIZ];
                        strcpy(tmp, lines[k]);
                        strcpy(lines[k], lines[k + 1]);
                        strcpy(lines[k + 1], tmp);
                        change = 1;
                    }
//             returnCleanRow(lines[k]); 
            }   
                
            if(change == 0){
                
                break;
            }
            }
            for(k = 0;k < i;k++){
            returnCleanRow(lines[k]);
            }
            
}   
void returnCleanRow(char * cont){
        char* token;
        int br = 1;
        char* tofree;
        char *string = strdup(cont);
       
        if (string != NULL) {

          tofree = string;

          while ((token = strsep(&string, "|")) != NULL)
          {
              if(br == 1){
              printf("Datum: %s\n\n",token,br);
              }else if(br ==2){
                printf("Obaveza: %s\n\n",token,br);  
              }else if(br == 3){
                 printf("Ostalo jos dana: %s\n\n",token,br); 
              }
              br++;
          }
          printf("---------------------------- \n\n");
           free(tofree);
        }
        
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


//WRITING