#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LENGTH 1024 // maximum size of command line input

int main() 
{

  char command[MAX_LENGTH]; // array to store command line input
  char *args[64]; // array to store arguments
  char *parsed; // temporary pointer to store parsed input
  int status; // status of child process
  pid_t pid; // process id of child

  printf("Shell is running...\n");

  while(1) 
  { // infinite loop for shell to run until exited 

    printf(">> "); // prompt for user input
    fgets(command, MAX_LENGTH, stdin); // read in command line input

    parsed = strtok(command, " \n"); // parse input into tokens
    int i = 0;

    while(parsed != NULL) 
    { // loop through tokens and add to args array
      args[i++] = parsed;
      parsed = strtok(NULL, " \n");
    }

    args[i] = NULL; // set last element to NULL (as per execv requirements)

    pid = fork(); // fork the process to create child

    if(pid < 0) { // error checking
      printf("Error: Failed to fork\n");
      exit(EXIT_FAILURE);
    } 
    else if(pid == 0) 
    { // child process
      if(execvp(args[0], args) < 0) { // execute command with arguments
        printf("Error: Failed to execute command\n");
        exit(EXIT_FAILURE);
      }
    } 
    else { // parent process
      wait(&status); // wait for child
      if(status != 0) 
      { // error handling for child failure
        printf("Error: Child failed to execute command\n");
      }
    }

  }

  return 0;
}
