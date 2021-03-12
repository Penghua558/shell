#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "builtincmd.h"

int PATH_NUM = 3;
const char* builtInCmd[BUILTIN_CMD_NUM] = {"exit",
                            "cd",
                            "path"};

char* path[PATH_MAXNUM]= {"/bin",
                                "/usr/bin",
                                "/sbin"};

int inCmdArray(char* cmd, const char* cmdSet[]) {
    // check if command is in builtInCmd array or not
    // if command is in array, then return 0 otherwise return -1
    for (int i=0; i<BUILTIN_CMD_NUM; i++) {
        if (!strcmp(cmdSet[i], cmd))
            return 0;
    }
    return -1;
}

int builtInExec(struct cmdent cmd) {
    // find out which command to execute, then execute it
    if (!strcmp(cmd.args[0], "exit")) {
        exit(0);
        return 0;
    }
    if (!strcmp(cmd.args[0], "cd")) {
        if (cd(cmd) == 0)
            return 0;
        else
            return -1;
    }
    if (!strcmp(cmd.args[0], "path")) {
        if (setPath(cmd) == 0)
            return 0;
        else
            return -1;
    }
    return -1;
}


int cd(struct cmdent cmd) {
   if (cmd.argnum != 1)
       // cd accepets only and must one argument
       return -1;

   if (chdir(cmd.args[1]) == -1)
       // change directory failed
       return -1;
   else 
       return 0;
}


int setPath(struct cmdent cmd) {
    if (cmd.argnum < 1)
        // path built-in command must take at least one argument
        return -1;
    for (int i=1; i<=cmd.argnum; i++) {
       path[i-1] = cmd.args[i]; 
    }
    path[cmd.argnum] = "\0";
    for (int i=cmd.argnum; i<PATH_MAXNUM; i++) {
        path[i] = NULL;
    }
    PATH_NUM = cmd.argnum;
    /* for (int i=0; i<PATH_NUM; i++) */
    /*     printf("%s ", path[i]); */
    /* printf("\n"); */
    return 0;
}
