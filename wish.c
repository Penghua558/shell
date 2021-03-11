#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "checkexec.h"
#include "shellmisc.h"
#include "paraexec.h"

int main(int argc, char* argv[]) {
    /* char error_message[30] = "An error has occurred\n"; */
    if (argc == 1) {
        // interactive mode
        while (1) {
            char* line = NULL;
            size_t len = 0;
            ssize_t nread;
            FILE* input = stdin;
            char c = '\0';
            printf("wish>");
            c = getchar();
            if ((c != EOF) && (c != '\n')) {
                if ((nread = getline(&line, &len, input))== -1) {
                    /* fprintf(stderr, "errorno: %s\n", strerror(errno)); */
                    write(STDERR_FILENO, error_message, strlen(error_message));
                    exit(1);
                }
                line[nread-1] = '\0'; // nread-1 contains \b, clear it

                char* usrline = (char*) malloc(1+strlen(line));
                usrline[0] = c;
                strcat(usrline,line);
                free(line);

                /* printf("usrline generated\n"); */

                //extract command from usrline
                int* cmdnum = malloc(sizeof(int));
                *cmdnum = 0;
                struct cmdent* cmdblk = extract(usrline, cmdnum);

                /* printf("commands extracted\n"); */

                /* char* cmd = (char*) malloc(sizeof(usrline)); */
                /* strcpy(cmd,usrline); */


                // build in command: exit
                if (!strcmp(cmdblk[0].args[0],"exit")) {
                    /* printf("compare command: %s with exit\n", cmdblk[0].args[0]); */
                    exit(0);
                }
                
                //check if command exists in directories and is executable
                /* char* pathname = NULL; */
                int* retval = malloc(sizeof(int));
                *retval = 0;
                // execute commands parallelly
                paraexec(cmdblk, cmdnum, retval);
                printf("finished executing commands\n");
                if (*retval == -1) {
                    write(STDERR_FILENO, error_message, strlen(error_message));
                }
                /* printf("retval: %d\n", *retval); */
                // after finishing all commands, free memory of cmdblk and retval
                free(cmdnum);
                free(usrline);
                free(retval);
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
