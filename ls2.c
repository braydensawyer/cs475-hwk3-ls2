#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls2.h"

//Form the full path name by concatetnating path and file name
char * fullPathName(char* path, char* name) {
    int length = strlen(path) + strlen(name) + 2;
    char * fullName = (char*)malloc(length);
    memset(fullName, 0, length);
    strcat(fullName, path); 
    strcat(fullName, "/");
    strcat(fullName, name); 
    return fullName;
}

//Mode 1 function to list files and directories on the given path
void m1(char path[], stack_t *s, int indent){
    DIR* folder = opendir(path); 
    struct stat info; 
    struct dirent* file = readdir(folder);
    //loops until no more files
    while(file != NULL){
        //check for "." and ".."
        if(strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0){
            char* fullname = fullPathName(path, file->d_name);
            lstat(fullname, &info);
            //check if file is regular 
            if(S_ISREG(info.st_mode) == 1){
                char s1[10];
                sprintf(s1, "%ld", info.st_size);
                //format regular file string and push
                int len = strlen(INDENT) * indent + strlen(file->d_name) + strlen(" (") + 11 + strlen(" bytes)");
                char* s2 =  (char*)malloc(len);
                memset(s2, 0, len);
                for(int i = 0; i < indent; i++){
                    strcat(s2, INDENT); 
                }
                strcat(s2, file->d_name);
                strcat(s2, " (");
                strcat(s2, s1);
                strcat(s2," bytes)");
                strcat(s2, "\0");
                push(s, s2);
            }
            //check if file is directory 
            if(S_ISDIR(info.st_mode) == 1){
                char* s1 = fullPathName(path, file->d_name);
                m1(s1, s, indent + 1);

                //format directory string and push
                int len = strlen(INDENT) * indent + strlen(file->d_name) + strlen("/ (directory)") + 1;
                char* s0 = (char*)malloc(len); 
                memset(s0, 0, len);
                for(int i = 0; i < indent; i++){
                    strcat(s0, INDENT); 
                }
                strcat(s0, file->d_name); 
                strcat(s0, "/ (directory)"); 
                strcat(s0, "\0");
                push(s, s0); 
                free(s1);
            }
            free(fullname);
        }
        file = readdir(folder);
    }
    
    closedir(folder);
    free(file);
}

//Mode 2 function to search for a target file in the given path
int m2(char path[], char target[], stack_t *s, int indent){
    int found = 0;
    DIR* folder = opendir(path); 
    struct stat info; 
    struct dirent* file = readdir(folder);
    //loops until no more files
    while(file != NULL){
        //check for "." and ".."
        if(strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0){
            char* fullname = fullPathName(path, file->d_name);
            lstat(fullname, &info);
            //check to see if file is regular 
            if(S_ISREG(info.st_mode) == 1){
                //check to see if file is target file
                if(strcmp(file->d_name, target) == 0){
                    //file is found set found to true 
                    found = 1; 
                    char s1[10];
                    sprintf(s1, "%ld", info.st_size);
                    //format regular file string and push 
                    int len = strlen(INDENT) * indent + strlen(file->d_name) + strlen(" (") + 11 + strlen(" bytes)");
                    char* s2 =  (char*)malloc(len);
                    memset(s2, 0, len);
                    for(int i = 0; i < indent; i++){
                        strcat(s2, INDENT); 
                    }
                    strcat(s2, file->d_name);
                    strcat(s2, " (");
                    strcat(s2, s1);
                    strcat(s2," bytes)");
                    strcat(s2, "\0");
                    push(s, s2);
                }
            }
            //check if file is directory 
            if(S_ISDIR(info.st_mode) == 1){
                char* s1 = fullPathName(path, file->d_name);
                int ifFound = m2(s1, target, s, indent + 1);
                //check if targetfile is found in directory
                if(ifFound == 1){
                    //set found to true for parent directories 
                    found = 1; 
                    //format directory string and push
                    int len = strlen(INDENT) * indent + strlen(file->d_name) + strlen("/ (directory)") + 1;
                    char* s0 = (char*)malloc(len); 
                    memset(s0, 0, len);
                    for(int i = 0; i < indent; i++){
                        strcat(s0, INDENT); 
                    }
                    strcat(s0, file->d_name); 
                    strcat(s0, "/ (directory)"); 
                    strcat(s0, "\0");
                    push(s, s0); 
                }
                free(s1);
            }
            free(fullname);
        }
        file = readdir(folder);
    }
    closedir(folder);
    free(file);
    return found; 
}
