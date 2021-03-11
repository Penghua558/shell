#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "paraexec.h"
#include "checkexec.h"
#include "shellmisc.h"


void paraexec(struct cmdent* cmdblk, int *cmdnum, int* retval) {
    // given a set of commands, execute them parallelly, store return value in variabel 
    // retval, -1 if failed to execute command,
    // return 0 if successfully executed the command
    
    char* pathname = NULL;
    int status;
    int rc;
    for (int i=0; i<*cmdnum; i++) {
        // check if the command exists and executable
        if ((pathname = check(cmdblk[i].args[0])) == NULL) {
            *retval = -1;
        } else {
            cmdblk[i].args[0] = pathname;
            // execute shell command
            rc = fork(); // fork a new child process to execute shell command
            if (rc < 0) {
                *retval = -1;
            } else if (rc == 0) {
                // in child process, execute shell command
                char* arg[cmdblk[i].argnum+2];
                for (int j=0; j<cmdblk[i].argnum+1; j++)
                    arg[j] = cmdblk[i].args[j];
                arg[cmdblk[i].argnum+1] = NULL;
                if (execv(pathname, arg) == -1) {
                    *retval = -1;
                }
            } else {
                // parent process wait for child process
                // because current command number is larger than 2, we need to execute them
                // in parallel
                wait(&status);
            }
            *retval = 0;
        }
    }
    // after finishing all commands, free memory of cmdblk
}
