/* Corrine Smith
 * CSCI 315
 * Lab 11
 * 11/28/2017
 */

#include "wrappers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include "dnode.h"
#include "dlist.h"

void calendar(int year, int month);
int check_leap_year(int year);          
int total_leap_years(int year);         
int total_days(int y, int m, int d);    
long days(int y, int m, int d);         
void display_calendar(int y, int m); 

struct dlist *history;

//Checks the string to see if it contains a tab. Returns 0 if a tab is found in the string, 0 otherwise.
int check_tab(char *buffer){        //searches string and tab is not found
        if(strchr(buffer,'\t') == NULL){
                return -1;
        } else{ //tab found
                return 0;
        }
}

/**Creates a doubly-linked list to store all commands entered.**/
void history_init(){
    history = dlist_create();
    return;
}

void calendar(int year, int month) {
  	/* gets the month and yead for the desired calendar 
   	* returns -1 on error, 0 on success 
   	*/

  	if (month < 1 || month > 12) {
		printf("Invalid entry. Enter [year] [month]\n");

		return;
  	}

  	display_calendar(year, month);

  	return;
	}

int check_leap_year(int y) {
	/* Returns 1 if leap year, 0 for common year */

	if (0 == (y % 400) ){
		return 1;

	} else if (0 == (y % 100) ) {
		return 0;

	} else if (0 == (y % 4) ) {
		return 1;

	} else {
		return 0;

  	}
}

int total_leap_years(int y){
  	/* The number of leap year */

  	int leap_years;
  	leap_years = y / 4 - y / 100 /* common year */ + y / 400;

  	return leap_years;
}

int total_days(int y, int m, int d) {
  	/* Gets the total number of days since the beginning of the year */

  	int num_days = 0;
  	static int days[] = { -1, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

	if (m > 2 && check_leap_year(y)){ //account for leap year
		num_days = 1;
	}

	num_days += days[m];
	num_days += d;

  	return num_days;
}

long days(int y, int m, int d) {

  	int prev_year;
  	int num_days;

  	prev_year = y - 1;
  	num_days = 365L * prev_year + total_leap_years(prev_year) + total_days(y, m, d);

 	return num_days;
}

void display_calendar(int y, int m) {
  	/* display calendar at m y */

  	const char *Month[] = { NULL,"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
  	char week[] = "Su Mo Tu We Th Fr Sa";
  	int num_days[] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  	int top_week;
  	int i;
  	int day;

  	top_week = days(y, m, 1) % 7;

  	if (check_leap_year(y)) {
     		num_days[2] = 29;
  	}
  	
	printf("\n     %s %d\n%s\n", Month[m], y, week);

  	for (i = 0; i < top_week; i++) {
    		printf("   ");
  	}

  	for (i = top_week, day = 1; day <= num_days[m]; i++, day++) {
    		printf("%2d ", day);
    		if (i % 7 == 6) {
      			printf("\n");
    		}
  	}

  	printf("\n");
}

int executeCommand(char **args, struct dlist *history, int count){
	int status;
	char *command = args[0];
	args[count] = NULL;	
	if(strcmp(command, "cd") == 0){
		status = 0;
		if(args[1] == NULL){
			status = chdir(getenv("HOME"));
		}
		else{
			char *directory = args[1];
			status = chdir(directory);
		}
		if(status == 0){
			printf("directory change complete\n");
		}
		else{
			printf("unable to change directory: %s\n", strerror(errno));
		}
	}
	else if(strcmp(command, "exit") == 0){
		exit(0);
	}
	else if(strcmp(command, "calendar") == 0){
		calendar(atoi(args[1]), atoi(args[2]));
		printf("gshell: program terminated properly\n");
	}
	else if(strcmp(command, "history") == 0){
		//Prints the user's command history
		printf("\nCOMMAND HISTORY\n");                                                                                                                                                                                                                                                   
		struct dnode *curr_node = history->front;
		while(curr_node != NULL){
			if(curr_node->data != NULL){
    			printf("%s\n", curr_node->data);
			}
			curr_node = curr_node->next;
		}	
		printf("\n");
	}	
	else{
		for(int i = 0; i < count; i++){
			strcat(args[i], "\0");
		}
		pid_t pid = Fork();
		if(pid > 0){
			//parent process
			Wait(&status);
		}
		else{
			//child process
			int ret_val = execvp(command, args);
			if(ret_val == -1){
				perror("invalid command or args");
				exit(-1);
			}
		}
	}
	return status;
}

int checkPipe(char **args, int count){
	for(int i = 0; i < count; i++){
		if(strcmp(args[i], "|") == 0){
			return i;
		}
	}
	return 0;
}

int executePipe(char **args, int pipe, int count){
	//uses dup2 to redirect output to be input
	char **args1 = (char **)calloc(4, 50*(sizeof(char)));
	char **args2 = (char **)calloc(4, 50*(sizeof(char)));
	int count1 = 0;
	int count2 = 0;
	for(int i = 0; i < pipe; i++){
		args1[i] = args[i];
		count1++;
	}
	for(int i = pipe+1; i < count; i++){
		args2[i-pipe-1] = args[i];
		count2++;
	}

	char *command1 = args1[0];
	char *command2 = args2[0];

	int pipefd[2];
	int pid;

	Pipe(pipefd);

	pid = Fork();

	int status = 0;

	if(pid == 0){
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		status = execvp(command1, args1);
		
	}

	else{
		pid = Fork();
		if(pid == 0){
			dup2(pipefd[0], 0);
			close(pipefd[1]);
			status = execvp(command2, args2);
		}
		else{
			Wait(&status);
		}
	}
	return status;
}



int main(){
	char string[100];
	pid_t pid;
	int status = 0;
	char *command;
	char **args;

	history_init();

	while(true){
		printf("gshell> ");
		fgets(string, 100, stdin);
		if(strcmp(string, "\n") == 0){
			fgets(string, 100, stdin);
			if(strcmp(string, "\n") == 0){
				args = (char **)calloc(6, 50*sizeof(char));
				args[0] = "ls";
				pid = Fork();
				if(pid == 0){
					execvp("ls", args);
				}
				else{
					Wait(&status);
				}
			}
		}

		else if(check_tab(string) == 0){
                        //resets the input string
                        memset(string, 0, 100);
                        //sets the string to pwd, which will print the full directory path      
                        strcat(string, "pwd");
                }

		char *input;
		
		
		input = strdup(string);
		
		char *token1;
		token1 = strtok_r(input, ";", &input);
		while(token1 != NULL){ 
			args = (char **)calloc(6, 50*sizeof(char));
			char *token;
			char *temp;
			token = strtok(token1, " ");	
			int count = 0;
			while(token != NULL){
				char *temp = strchr(token, '\n');
				if (temp)  *temp = 0;
				args[count] = token;
				count++;
				token = strtok(NULL, " ");
			}
			int pipe = checkPipe(args, count);			
			if(pipe != 0){
				status = executePipe(args, pipe, count);
			}
			else{	
				status = executeCommand(args, history, count);
			}
		
			if(status == 0){
                                printf("gshell: program terminated successfully\n");
				//Add the string to the back of the history list and print
				if(pipe == 0){
					dlist_add_back(history, token1);
    					printf("Command %s added to history\n", token1);
				}
				else{
					dlist_add_back(history, args[0]);
					printf("Command %s added to history\n", args[0]);
					dlist_add_back(history, args[pipe+1]);
					printf("Command %s added to history\n", args[pipe+1]);
				}
                        }
                	else{
                                printf("gshell: program terminated abnormally: %d\n", status);
                        }
			
			free(args);
			token1 = strtok_r(input, ";", &input);
		}
				
	}
}	

