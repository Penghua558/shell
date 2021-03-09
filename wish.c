#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "checkexec.h"

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

                char* usrline = (char*) malloc(1+sizeof(line));
                usrline[0] = c;
                strcat(usrline,line);
                free(line);

                //extract command for usrline
                char* cmd = (char*) malloc(sizeof(usrline));
                strcpy(cmd,usrline);


                // build in command: exit
                if (!strcmp(cmd,"exit"))
                    exit(0);
                
                //check if command exists in directories and is executable
                char* pathname = NULL;
                if ((pathname = check(cmd)) == NULL) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    free(cmd);
                    /* exit(1); */
                } else {
                    free(cmd);
                    char* arg_list[] = {pathname, NULL};
                    /* printf("main function: %s\n", pathname); */

                    // execute shell command
                    int rc = fork(); // fork a new child process to execute shell command
                    if (rc < 0) {
                        write(STDERR_FILENO, error_message, strlen(error_message));
                        exit(1);
                    } else if (rc == 0) {
                        // in child process, execute shell command
                        if (execv(pathname, arg_list) == -1) {
                            write(STDERR_FILENO, error_message, strlen(error_message));
                            /* exit(1); */
                        }
                    } else {
                        // parent process wait for child process
                        waitpid(rc, NULL, 0);
                    }
                }
            } else if (c == EOF) {
                // if user input EOF, exit program gracefully
                printf("\n");
                exit(0);
            }
        }
    }
    return 0;
}
