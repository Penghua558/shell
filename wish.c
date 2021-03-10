#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "checkexec.h"
#include "shellmisc.h"

int main(int argc, char* argv[]) {
    char error_message[30] = "An error has occurred\n";
    if (argc == 1) {
        // interactive mode
        while (1) {
            char* line = NULL;
            size_t len = 0;
            ssize_t nread;
            FILE* input = stdin;
            char c;
            printf("wish>");
            c = getchar();
            if ((c != EOF) && (c != '\n')) {
                if ((nread = getline(&line, &len, input))== -1) {
                    /* fprintf(stderr, "errorno: %s\n", strerror(errno)); */
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    exit(1);
                }
                line[nread-1] = '\0'; // nread-1 contains \b, clear it

                char* usrline = (char*) malloc(2+strlen(line));
                usrline[0] = c;
                strcat(usrline,line);
                free(line);

                //extract command from usrline
                int* cmdnum = NULL;
                int tmp = 0;
                cmdnum = &tmp;
                struct cmdent* cmdblk = extract(usrline, cmdnum);

                char* cmd = (char*) malloc(sizeof(usrline));
                strcpy(cmd,usrline);


                // build in command: exit
                if (!strcmp(cmdblk[0].args[0],"exit"))
                    exit(0);
                
                //check if command exists in directories and is executable
                char* pathname = NULL;
                if ((pathname = check(cmdblk[0].args[0])) == NULL) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    /* exit(1); */
                } else {
                    /* char* arg_list[] = {pathname, NULL}; */
                    cmdblk[0].args[0] = pathname;
                    // execute shell command
                    int rc = fork(); // fork a new child process to execute shell command
                    if (rc < 0) {
                        write(STDERR_FILENO, error_message, strlen(error_message));
                        exit(1);
                    } else if (rc == 0) {
                        // in child process, execute shell command
                        if (execv(pathname, cmdblk[0].args) == -1) {
                            write(STDERR_FILENO, error_message, strlen(error_message));
                            /* exit(1); */
                        }
                    } else {
                        // parent process wait for child process
                        waitpid(rc, NULL, 0);
                    }
                }
                // after finishing all commands, free memory of cmdblk
                free(cmdblk);
            } else if (c == EOF) {
                // if user input EOF, exit program gracefully
                printf("\n");
                exit(0);
            }
        }
    }
    return 0;
}
