CS332: Lab05

This assignment asked us to modify the source code (readdir.c or readdir_v2.c) and implement a function that will recursively traverse and list the directory's files and sub-directories files from a given directory path.

On VSCode, I was getting many errors having to do with the dirent.h file type descriptors but after switching over to Vulcan, all these errors went away. I compiled and ran the code on the Vulcan server which ran fine on my computer with no warnings or errors.

To test this code, you can compile by using 'gcc -o lab05 lab05.c' and to run the code use './lab05 (Directory Name)' 'ex. ./lab05 Homework'. This program will then list all the files contained in this Homework directory and if it hits a subdirectory it will list the under Homework/sub-directory.

Outside References:
https://stackoverflow.com/questions/63831098/how-to-list-all-files-of-a-directory-recursively-in-c