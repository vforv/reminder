/*
 * File:   main.c
 * Author: root
 *
 * Created on June 26, 2015, 7:31 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include <stddef.h>
#define TRUE  1
#define FALSE 0
#include <conio.h>


char createDatabaseIfNotExists();
void readFileAndCreateTable();
time_t to_seconds(const char *date);
void returnCleanRow(char * cont);
/*
 *
 */
void textcolor(int attr, int fg, int bg);
//MAIN CODE
int main(int argc, char** argv) {
    int choose = 2;


    if(createDatabaseIfNotExists("database")){

        printf("[+] DATABSE FILE EXISTS\n");
        puts("[+] INITIALIZATION STARTED...\n");
        readFileAndCreateTable();
        puts("To insert new date into database 1");
        scanf(" %d",&choose);
        if(choose == 1){
           insertNewRow();
        }else{
            puts("You pressed wrong button.");
        }


    }else{
        printf("[-] DATABASE FILE NOT EXISTS");
        readFileAndCreateTable();
         puts("To insert new date into database 1");
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
        puts("[+] DATABASE FILE CREATED\n");
        puts("[+] INITIALIZATION STARTED...\n");
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
                date1 = strtok(string, "|");
                date2 = strtok(string1, "|");
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
            token = strtok(string, "|");
          while (token != NULL)
          {
              if(br == 1){
                printf("Datum: %s\n", token);
              }else if(br == 2){
                printf("Obaveza: %s\n", token);
              }else if(br == 3){
                printf("U koliko sati je obaveza: %s\n", token);
              }

              br++;
              token = strtok(NULL,"|");
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

        p=(char *)sscanf(date,"%d-%b-%Y",&storage);
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

