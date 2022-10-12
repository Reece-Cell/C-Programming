#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

/*
 * A very simple shell that supports only commands 'exit', 'help', and 'today'.
 */

#define MAX_BUF 160
#define MAX_TOKS 100

int main() {
        int ch;
        char *pos;
        char s[MAX_BUF+2];   // 2 extra for the newline and ending '\0'
        static const char prompt[] = "msh> ";
        char *toks[MAX_TOKS];

        //Declaring our token and counter that we'll use
        char *arrtoken;
        int counter = 0;
        int i = 0;
        //Declaring our dates and time variables
        char *today = "today";
        char *help = "help";
        char *exit = "exit";
        time_t update;
        time(&update);
        struct tm *calendar = localtime(&update);
        int day = calendar->tm_mday -1;
        int month = calendar->tm_mon + 1; 
        int year = calendar->tm_year + 1900;
        //My understanding of the time function was aided by tutorialspoint and techiedelight

        while (1) {
                // prompt for input if input from terminal
                if (isatty(fileno(stdin))) {
                        printf(prompt);
                }

                // read input
                char *status = fgets(s, MAX_BUF+2, stdin);

                // exit if ^d entered
                if (status == NULL) {
                        printf("\n");
                        break;
                }

                // input is too long if last character is not newline
                if ((pos = strchr(s, '\n')) == NULL) {
                        printf("error: input too long\n");
                        // clear the input buffer
                        while ((ch = getchar()) != '\n' && ch != EOF) ;
                        continue;
                }

                // remove trailing newline
                *pos = '\0';

        arrtoken = strtok(s, " ");
        while(arrtoken != NULL){
            toks[counter] = arrtoken;
            arrtoken = strtok(NULL, " ");
            counter = counter + 1;
        }
        
        while (i < counter){
            char *token = toks[i];
            if(strcmp(token,exit) == 0 && i == 0){
                exit(EXIT_SUCCESS);
            }else if(strcmp(token,help) == 0 && i == 0){
                printf("enter 'help', 'today', or 'exit' to quit");
            }else if(strcmp(token,today)==0 && i == 0){
                printf("%02d/%02d/%d\n", month, day, year);
            }else{
            printf( "token: '%s", token );
            printf("'\n");
            }
            i = i + 1;
        }
    }
        exit(EXIT_SUCCESS);
}