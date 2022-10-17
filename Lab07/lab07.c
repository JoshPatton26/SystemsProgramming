#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

/*
* Function to create an array from each line that comes from the input file
* Accepts a char pointer containing the line of data, and argv from main.
* Returns array filled with linux commands from the test2.txt.
*/
char** createArr(char *line, char **arga){
    int i = 1;
    char *token = strtok(line, " \n");

    // Allocate memory for the array, as well as the first element of the array.
    arga = (char **) malloc(100*sizeof(char*));
    arga[0] = (char *) malloc(sizeof(char)*BUFSIZ);

    // Tokenize the first element of the txt file.
    strcpy(arga[0], token);
    
    // Loop through the rest of the contents in the txt file and tokenize each and store in array.
    while(token != NULL){
        
        token = strtok(NULL, " \n");

        // If the token is not null, allocate memory then copy the next command arg to next index of array and increment i.
        if (token != NULL){
            arga[i] = malloc(sizeof(char)*BUFSIZ);
            strcpy(arga[i], token);
            i++;
        }
    }
    // Set the last index equal to NULL.
    arga[i] = NULL;
    // Return the array with the line from the input file tokenized into eacg element.
    return arga;
}

int main(int argc, char **argv){
    pid_t pid;
    int status;
    time_t start, end;

    // To hold the whole line of the file contents.
    char *line = malloc(sizeof(char) * BUFSIZ);

    // Make sure the command is entered properly.
    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    // Open file given in the command argument for input, reading only.
    FILE *fp = fopen(argv[1], "r");
    // Open the outputlog.txt for printing results from child process execvp(), write only.
    FILE *fp2 = fopen("outputlog.txt", "w");
    
    // Make sure the file in not NULL.
    if(fp == NULL){
        perror("Unable to open file");
        exit(1);
    }

    // Make sure the file in not NULL.
    if(fp2 == NULL){
        perror("Unable to open file2");
        exit(1);
    }

    // Loop through the content of the file reading it line by line.
    while(fgets(line, BUFSIZ, fp)!=NULL){

        // Create new array to send to function to get filled with file contents.
        char **arga ;
        // Create new array to hold args.
        char **args = malloc(sizeof(char) * BUFSIZ);

        // Print the linux argument being executed to the outputlog.txt file.
        fprintf(fp2, "%s", line);

        // Call function to create array out of the files contents.
        args = createArr(line, arga);
        // Print the first four elements of args[] for visual purposes.
        printf("%s %s %s %s\n", args[0], args[1], args[2], args[3]);

        // Call fork() to create a new process which will be the child process.
        pid = fork();

        if(pid == 0){ /* Child Process */
            execvp(args[0], args);
            printf("If you see this execvp() is not executing...");
        }else if(pid > 0){ /* Parent Process */
            // Get the starting time of child process execution.
            time(&start);
            // Wait for the child process to finish executing.
            wait(&status);
            if (WIFEXITED(status)) { /* child process terminated normally */
                // Get the end time of the child process execution.
                time(&end);
                // Print the start and end times to outputlog.txt.
                fprintf(fp2, "\tStart time: %s\tEnd time: %s\n",ctime(&start), ctime(&end));
                // Print the exit status of the child process.
                printf("Child process exited with status = %d\n\n", WEXITSTATUS(status));
            } else { /* child process did not terminate normally */
                printf("Child process did not terminate normally!\n");
            }
        }else{
            printf("Big time error bud\n");
        }
    }

    // Print the start and end times to the terminal.
    printf("\nStart time = %sEnd time = %s", ctime(&start), ctime(&end));

    // Close both files.
    fclose(fp);
    fclose(fp2);

    return 0;
}