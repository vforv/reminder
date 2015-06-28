/* 
 * File:   main.c
 * Author: root
 *
 * Created on June 26, 2015, 7:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#include <string.h>
#include <time.h>

#define TRUE  1
#define FALSE 0

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
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
    int choose = 2;
      
    if(createDatabaseIfNotExists("database")){
        printf(KGRN "[+] " RESET "DATABSE FILE EXISTS\n");
        puts(KGRN "[+] " RESET "INITIALIZATION STARTED...\n");
        readFileAndCreateTable();
        puts("To insert new date into database " KRED "1" RESET);
        scanf(" %d",&choose);
        if(choose == 1){
           insertNewRow();
        }else{
            puts("You pressed wrong button.");
        }
        
        
    }else{
        printf(KRED "[-] " RESET "DATABASE FILE NOT EXISTS");
        readFileAndCreateTable();
         puts("To insert new date into database " KRED "1" RESET);
         scanf(" %d",&choose);
         if(choose == 1){
           insertNewRow();
        }else{
            puts("You pressed wrong button.");
        }
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
            for(k = 0;k < i - 1;k++){
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
              printf(KBLU "Datum: " RESET "%s \n",token,br);
              }else if(br ==2){
                printf(KGRN "Obaveza: " RESET "%s\n",token,br);  
              }else if(br == 3){
                 printf(KMAG "U koliko sati je obaveza: " RESET "%s\n",token,br); 
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

        p=strptime(date,"%d-%b-%Y",&storage);
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

int insertNewRow(){
    int cont = 1;
    
    
    while(cont == 1){
    struct timeval tv;
    char str[12];
    struct tm *tm;
    
    int days = 1;
    char obligation[20];
    char dodatno[20];
    
    puts("Enter nuber of days till obligation:\n");
    scanf(" %d", &days);
    puts("Enter obligation:\n");
    scanf(" %s", obligation);
    puts("Sati:\n");
    scanf(" %s", dodatno);
    
    if (gettimeofday(&tv, NULL) == -1)
        return -1; /* error occurred */
    tv.tv_sec += days * 24 * 3600; /* add 6 days converted to seconds */
    tm = localtime(&tv.tv_sec);
    /* Format as you want */
    
    strftime(str, sizeof(str), "%d-%b-%Y", tm);
    
    FILE * database;
    database = fopen("database", "a+");
    fprintf(database, "%s|%s|%s \n",str,obligation,dodatno);
    fclose(database);
    
    puts("To finish with adding enter 0 to continue press 1 \n");
    scanf(" %d", &cont);
    }
   readFileAndCreateTable();
}

