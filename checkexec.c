#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "checkexec.h"
#include "builtincmd.h"


char* check(char* cmd) {
    // check if cmd is accessible and executable
    for (int i = 0; i < PATH_NUM; i++) {
       char* pathname = (char*) malloc(strlen(path[i])+1+strlen(cmd)+2); 
       /* char pathname[strlen(path[i])+strlen(cmd)]; */
       strcpy(pathname, path[i]);
       pathname[strlen(path[i])] = '/';
       pathname[strlen(path[i])+1] = '\0';
       strcat(pathname, cmd);
       /* printf("check function: %s\n", pathname); */
       if (access(pathname, X_OK) == 0) {
           return pathname;
       }
       /* free(pathname); */
    }
    return NULL;
} 
