#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

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
    Function accepts an unsigned char pointer that points to the given directory path.
    This will then open and read all contents contained in this directory and prints all
    files and all sub-directory files contained.
*/
void traverseFiles(unsigned char *usrpath){
    printf("%s\n", usrpath);
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(usrpath);

    // Error with opening directory.
    if(!dir){
        printf ("Error opening directory '%s'\n", usrpath);
        exit (-1);
    }

    // Loop through the files in the given directory and print all directory file and sub-directory files.
    int count = 1;
    while((dp = readdir(dir)) != NULL){
        if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
            printf("[%d] %s (%s)\n", count, dp->d_name, filetype(dp->d_type));

            char *type = filetype(dp->d_type);

            // Check to see if a sub-directory. If so, form a new path and call the function again.
            if(strcmp(type, "directory") == 0){
                // Construct a new path from basePath.
                strcpy(path, usrpath);
                strcat(path, "/");
                strcat(path, dp->d_name);
                traverseFiles(path);
            }
            count++;
        }
    }
    closedir(dir);
}

int main (int argc, char **argv) {
    struct dirent *dirent;
    DIR *parentDir;
    // Used to assign to argv[1], which is the given name of directory.
    unsigned char *usrpath;
    usrpath = malloc(strlen(argv[1]) + 1);
    strcpy(usrpath, argv[1]);

    // Check to make sure the user entered the command correctly.
    if (argc < 2) {
        printf ("Usage: %s <dirname>\n", argv[0]);
        exit(-1);
    }

    // Call function to traverse and print all files in given directory and and sub-directories included in given path.
    traverseFiles(usrpath);

    return 0;
}