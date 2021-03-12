#ifndef BUILTINCMD_H
#define BUILTINCMD_H

#include <stdlib.h>
#include <stdio.h>
#include "shellmisc.h"

// maximum path enviroments variable that can hold
#define PATH_MAXNUM 20
// number of built-in commands
#define BUILTIN_CMD_NUM 3

//path enviroments
extern int PATH_NUM;
extern const char* builtInCmd[3];
extern char* path[PATH_MAXNUM];

int inCmdArray(char* cmd, const char* cmdSet[]); 
// check if command is in builtInCmd array or not
int builtInExec(struct cmdent cmd); // find out which command to execute, then execute it
int cd(struct cmdent cmd);
int setPath(struct cmdent cmd);

#endif
