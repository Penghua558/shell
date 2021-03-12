#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "paraexec.h"
#include "checkexec.h"
#include "builtincmd.h"


void paraexec(struct cmdent* cmdblk, int *cmdnum) {
    // given a set of commands, execute them parallelly, store return value in variabel 
    // retval, -1 if failed to execute command,
    // return 0 if successfully executed the command
    
    char* pathname = NULL;
    int status;
    int rc;
    for (int i=0; i<*cmdnum; i++) {
        // check if the command is one of built-in commands
        if (inCmdArray(cmdblk[i].args[0], builtInCmd) == 0) {
           // the command is a built-in command 
           if (builtInExec(cmdblk[i]) != 0) {
               write(STDERR_FILENO, error_message, strlen(error_message));
           }
           continue;
        } 

        // check if the command exists and executable
        if ((pathname = check(cmdblk[i].args[0])) == NULL) {
            write(STDERR_FILENO, error_message, strlen(error_message));
        } else {
            cmdblk[i].args[0] = pathname;

            printf("path[0]: %s\n", path[0]);

            // execute shell command
            rc = fork(); // fork a new child process to execute shell command
            if (rc < 0) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
            } else if (rc == 0) {
                // in child process, execute shell command
                char* arg[cmdblk[i].argnum+2];
                for (int j=0; j<cmdblk[i].argnum+1; j++)
                    arg[j] = cmdblk[i].args[j];
                arg[cmdblk[i].argnum+1] = NULL;
                if (execv(pathname, arg) == -1) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
                }
            } else {
                // parent process wait for child process
                // because current command number is larger than 2, we need to execute them
                // in parallel
                wait(&status);
            }
        }
    }
    // after finishing all commands, free memory of cmdblk
}
