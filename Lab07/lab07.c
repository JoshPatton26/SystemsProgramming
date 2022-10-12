#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define BUFFSIZE 5000

char** createArr(char *line, char **arga){
    int i = 1;
    char *token = strtok(line, " \n");

    arga = (char **) malloc(100*sizeof(char*));
    arga[0] = (char *) malloc(sizeof(char)*BUFSIZ);
    strcpy(arga[0], token);

    //printf("arga[0]:%s \n", arga[0]);
    
    while(token != NULL){
        
        token = strtok(NULL, " \n");

        if (token != NULL){
            arga[i] = malloc(sizeof(char)*BUFSIZ);
            strcpy(arga[i], token);
            //printf("arga[%d]:%s \n", i, arga[i]);
        }
        
        i++;
    }
    arga[i] = NULL;
    return arga;
}

int main(int argc, char **argv){
    pid_t pid;
    int status;
    time_t start, end;

    // To hold the whole line of the file contents.
    char *line = malloc(sizeof(char) * BUFSIZ);

    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    FILE *fp = fopen(argv[1], "r");
    FILE *fp2 = fopen("outputlog.txt", "w");
    
    if(fp == NULL){
        perror("Unable to open file");
        exit(1);
    }

    if(fp2 == NULL){
        perror("Unable to open file2");
        exit(1);
    }

    while(fgets(line, BUFSIZ, fp)!=NULL){

        // Create new array to send to function to get filled with file contents.
        char **arga ;
        // Create new array to hold args.
        char **args = malloc(sizeof(char) * BUFSIZ);

        // Call function to create array out of the files contents.
        //printf("%s \n", line);
        fprintf(fp2, "%s", line);
        args = createArr(line, arga);
        //printf("%s %s %s %s\n", args[0], args[1], args[2], args[3]);

        char *execmd = malloc(sizeof(char) * BUFSIZ);
        strcpy(execmd, line);
        strcat(execmd, "\t");
        //strcat(execmd, ctime(&start));
        //fputs(execmd, fp2);
        //fprintf(fp2, "%s\t%s\t%s\n", execmd, ctime(&start), ctime(&end));

        pid = fork();

        if(pid == 0){
            execvp(args[0], args);
            printf("If you see this execvp() is not executing...");
        }else if(pid > 0){
            time(&start);
            wait(&status);
            if (WIFEXITED(status)) { /* child process terminated normally */
                time(&end);
                //fprintf(fp2, "%s\t%s\t%s\n", line, ctime(&start), ctime(&end));
                printf("Child process exited with status = %d\n", WEXITSTATUS(status));
            } else { /* child process did not terminate normally */
                printf("Child process did not terminate normally!\n");
            }
        }else{
            printf("Big time error bud\n");
        }
        
    }
    //fprintf(fp2, "%s\t%s\t%s\n", line, ctime(&start), ctime(&end));
    //fprintf(fp2, "\t%s\t%s\n", ctime(&start), ctime(&end));

    fclose(fp);
    fclose(fp2);

    return 0;
}