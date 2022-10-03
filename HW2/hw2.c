#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

typedef void MYFUNC(unsigned char *usrpath);
long long showInfo(char *givenpath);

static char *lastaccess = "";
static char permissions[100];
static bool cs = false;
static bool s = false;
static bool flag = false;
static int  indcount = 0, maxsize = 0;

char *filetype(unsigned char type) {
    char *str;
    switch(type) {
        case DT_BLK: str = "block device"; break;
        case DT_CHR: str = "character device"; break;
        case DT_DIR: str = "directory"; break;
        case DT_FIFO: str = "named pipe (FIFO)"; break;
        case DT_LNK: str = "symbolic link"; break;
        case DT_REG: str = "regular file"; break;
        case DT_SOCK: str = "UNIX domain socket"; break;
        case DT_UNKNOWN: str = "unknown file type"; break;
        default: str = "UNKNOWN";
    }
    return str;
}
    /*
    * Function accepts an unsigned char pointer that points to the given directory path.
    * This will then open and read all contents contained in this directory and prints all
    * files and all sub-directory files contained.
    */
void traverseFiles(unsigned char *usrpath){
    printf("%s\n", usrpath);
    char path[1000];
    struct dirent *dp;
    //struct stat buf;
    DIR *dir = opendir(usrpath);

    // Error with opening directory.
    if(!dir){
        printf ("Error opening directory '%s'\n", usrpath);
        exit (-1);
    }

    // Loop through the files in the given directory and print all directory file and sub-directory files.
    int count = 1, i = 0;
    long long int filesize = 0;
    while((dp = readdir(dir)) != NULL){
        if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){

            // Constructs the current files path to send to showInfo().
            char filename[1000];
            strcpy(filename, usrpath);
            strcat(filename, "/");
            strcat(filename, dp->d_name);

            //free(permissions);
            permissions[0] = NULL;
            filesize = showInfo(filename);

            // Used for printing indentation.
            for(i=0; i <= indcount; i++){
                printf("\t");
            }

            if(cs == true && s == true){
                if(filesize <= maxsize){
                    printf("[%d] %s (%s) \t %lld bytes \t Last accessed at: %s \t Permissions: %s\n", 
                count, dp->d_name, filetype(dp->d_type), filesize, lastaccess, permissions);
                }
            }else if(cs == true){
                printf("[%d] %s (%s) \t %lld bytes \t Last accessed at: %s \t Permissions: %s\n", 
                count, dp->d_name, filetype(dp->d_type), filesize, lastaccess, permissions);
            }else if(s == true){
                if(filesize <= maxsize){
                    printf("[%d] %s (%s) \t %lld bytes\n", 
                    count, dp->d_name, filetype(dp->d_type), filesize);
                }
            }else if(flag == true){
                // Wasnt able to get this working... Ran out of time.
                printf("[%d] %s (%s)\n", count, dp->d_name, filetype(dp->d_type));
            }else{
                printf("[%d] %s (%s)\n", count, dp->d_name, filetype(dp->d_type));
            }
            
            // To determine whether current entity is a file or another directory.
            char *type = filetype(dp->d_type);

            // Check to see if a sub-directory. If so, form a new path and call the function again.
            if(strcmp(type, "directory") == 0){
                
                // Construct a new path from usrpath.
                strcpy(path, usrpath);
                strcat(path, "/");
                strcat(path, dp->d_name);
                indcount--;

                indcount++;
                // Recursive call back to this function.
                traverseFiles(path);
            }
            // Increments count to keep track of the number of files listed per directory.
            count++;
        }
    }
    closedir(dir);
}

/*
* Function accepts a char pointer that holds the current files path. Returns the size of the file 
* in bytes as a long long int.
*/
long long showInfo(char *givenpath){
    struct stat sb;
    if(stat(givenpath, &sb) == -1){
        printf("stat error opening %s\n", givenpath);
        exit(1);
    }else{
        // Get files last access time.
        lastaccess = ctime(&sb.st_atime);

        // Get files permissions.
        if(sb.st_mode && R_OK){
            strcat(permissions, "-r");
        }else{
            strcat(permissions, "--");
        }
        if(sb.st_mode && W_OK){
            strcat(permissions, "w");
        }else{
            strcat(permissions, "-");
        }
        if(sb.st_mode && X_OK){
            strcat(permissions, "x");
        }else{
            strcat(permissions, "-");
        }
    }
    return sb.st_size;
}

/*
* Function accepts argc, argv, unsigned char pointer containing users given directory, and a function 
* pointer that calls the recursive traversefiles() function. Used to determine which of the -S, -s, or
* -f arguments were contained in the command. Returns the call to traversefiles() function.
*/
void checkargs(int argc, char **argv, unsigned char *usrpath, MYFUNC *f){
    int option;
    while((option = getopt(argc, argv, "Ss:f")) != -1){
        switch(option){
            case 'S':
                printf("This command contains -S command.\n");
                cs = true;
                printf("%d\n", cs);
                break;
            case 's':
                printf("This command contains -s command.\n");
                s = true;
                maxsize = atoi(optarg);
                printf("%d %d\n", s, maxsize);
                break;
            case 'f':
                printf("This command contains -f command.\n");
                flag = true;
                printf("%d\n", flag);
                break;
            default:
                printf("Error\n");
        }
    }
    return f(usrpath);
}

int main (int argc, char **argv) {
    struct dirent *dirent;
    DIR *parentDir;
    // Used to hold the starting directories name.
    unsigned char *usrpath;

    if(argc == 1){
        // If no name specified for starting directory, set it to the current directory as "."
        usrpath = ".";
    }else{
        // Used to assign to argv[1], which is the given name of directory.
        usrpath = malloc(strlen(argv[1]) + 1);
        strcpy(usrpath, argv[1]);
    }

    /*
    * Function call to check specific arguments while passing a function pointer
    * to recursively list all directories and sub-directories and the files within.
    */
    checkargs(argc, argv, usrpath, traverseFiles);

    return 0;
}