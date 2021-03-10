#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shellmisc.h"

struct cmdent* extract(char* usrline, int* cmdnum) {
    // first seperate them by &, then for each command sepetate them by space and tab
    char* firstDelimiters = "&"; // set seperate symbols are space and tab
    char* secondDelimiters = " \t";
    char* pch;
    /* char** tokens = NULL; */
    char** commands = NULL;
    char** tmp = NULL;
    int delinum = 0; // record how much delimiters needed to be stored in total in usrline
    /* int cmdnum = 0; // record how many commands needed to be executed in usrline */
    pch = strtok(usrline, firstDelimiters);
    while (pch != NULL) {
        // because the first non-delimiters word is not NULL, so we assume the first word is 
        // command
        *cmdnum = *cmdnum+1;
        // allocate a larger memory block to tmp
        tmp = malloc(sizeof(char*)*(*cmdnum));
        // copy contents of tokens to tmp
        memcpy(tmp,commands,sizeof(char*)*(*cmdnum-1));
        // put new tokens into the last slot of tmp
        tmp[*cmdnum-1] = pch;
        
        // let commands array pointer points to tmp block
        free(commands);
        commands = tmp;
        
        // read a new token
        pch = strtok(NULL, firstDelimiters);
    }
    
    // if no command detected, then the function shall return NULL
    if (*cmdnum == 0) {
        return NULL;
    }
    
    int i = 0;
    int cmdnumtmp = *cmdnum;
    struct cmdent* cmdblk = (struct cmdent*) malloc(sizeof(struct cmdent)*(*cmdnum));
    for (i=0; i<*cmdnum; i++) {
        // for each command line, seperate them by space and tab, and store them into struct
        delinum = 0;
        pch = strtok(commands[i], secondDelimiters);
        while (pch != NULL) {
            cmdblk[i].args[delinum] = pch;
            delinum++;
            
            // read a new token
            pch = strtok(NULL, secondDelimiters);
        }

        // store command in the first element of args array of the struct
        cmdblk[i].argnum = delinum-1;
        if (cmdblk[i].argnum == -1)
            cmdnumtmp--;
    }
    *cmdnum = cmdnumtmp;
    
    // allocate a new memory block to store final result, in case cmdblk may contains space
    // command, we need to filter it out
    struct cmdent* result = (struct cmdent*) malloc(sizeof(struct cmdent)*(*cmdnum));
    int poscmdblk = 0;
    for (int i=0; i<*cmdnum; i++) {
       while (cmdblk[poscmdblk].argnum == -1) {
            poscmdblk++;
       }
       result[i] = cmdblk[poscmdblk];
       poscmdblk++;
    }  
    /* free(cmdblk); */
    return result;
}
