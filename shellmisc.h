#ifndef SHELLMISC_H
#define SHELLMISC_H

#include <stdlib.h>
#include <stdio.h>

#define MAX_ARGNUM 20

extern char error_message[30];
struct cmdent {
    int argnum; // store number of arguments, -1 indicates no command
    char* args[MAX_ARGNUM]; // store command and arguments
};

struct cmdent* extract(char* usrline, int* cmdnum); // given a user input line, the function 
                                       //seperate them from 
                                       // commands and arguments
                                       // return an array of cmdent struct if parallel
                                       // commands are detected

#endif
