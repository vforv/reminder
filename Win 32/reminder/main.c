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
            int which;
           while(1){
               int change = 0;
            for(k = 0;k < i - 1;k++){
                char *string = strdup(lines[k]);
                char *string1 = strdup(lines[k + 1]);
                date1 = strtok(string, "|");
                date2 = strtok(string1, "|");


                    which = getValue(date1,date2);

                    if(which == 1){
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

struct datum{
    int * day;
    int * month;
    int * year;
};


int getValue(char * date1,char * date2){
    struct datum prvi;
    struct datum drugi;


    char * token;
    int br =1;
    char* tofree;
    char *string = strdup(date1);
    tofree = string;
    token = strtok(string, "-");
          while (token != NULL)
          {
              if(br == 1){
               prvi.day = token;
              }else if(br == 2){
              prvi.month = token;
              }else if(br == 3){
                prvi.year = token;
              }
              token = strtok(NULL,"-");
              br++;
          }


    char * token1;
    int br1 =1;
    char* tofree1;
    char *string1 = strdup(date2);
    tofree1 = string1;
    token1 = strtok(string1, "-");

          while (token1 != NULL)
          {
              if(br1 == 1){
               drugi.day = token1;
              }else if(br1 == 2){
                drugi.month = token1;
              }else if(br1 == 3){
                drugi.year = token1;
              }
              token1 = strtok(NULL,"-");
              br1++;
          }
          int monthToIntPrvi = getMonthNum(prvi.month);
          int monthToIntDrugi = getMonthNum(drugi.month);

        if(strcmp(prvi.year, drugi.year)>0){

                return 1;
        }else if(strcmp(prvi.year, drugi.year)<0){

            return 0;
        }else if(strcmp(prvi.year, drugi.year)==0){

            if(monthToIntPrvi > monthToIntDrugi){
                return 1;
            }else if(monthToIntPrvi < monthToIntDrugi){
                return 0;
            }else if(monthToIntPrvi == monthToIntDrugi){
                if(strcmp(prvi.day, drugi.day) >0){
                    return 1;

                }else if(strcmp(prvi.day, drugi.day) < 0){
                    return 0;
                }else if(strcmp(prvi.day, drugi.day) == 0){
                    return 0;
                }
            }
        }


        free(tofree1);
        free(tofree);


}


int getMonthNum(char * name){
char *months[12] ={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
char *pointertoarray = &months;
int i;
    for(i = 1; i <= 12; i++){
        if(strcmp(months[i], name)==0){
            return i;
        }
    }
}



//WRITING

int insertNewRow(){
    int cont = 1;


    while(cont == 1){
    struct timeval tv;
    char str[12];
    struct tm *tm;

    int days = 1;
    char obligation[1500];
    char dodatno[1500];

    puts("Enter nuber of days till obligation:");
    scanf(" %d%*c", &days);

    readString(obligation, "Enter obligation \n", 1500);
    readString(dodatno, "Enter hours \n", 1500);

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


void readString(char *array, char * prompt, int size) {
    printf("%s", prompt);
    int c; int count=0;
    while ((c = getchar()) != '\n' && c != EOF) {
        array[count] = c; count++;
        if (count == (size - 1)) { break; }
    }

    array[count] = '\0';
}

