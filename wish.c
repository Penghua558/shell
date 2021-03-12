#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "checkexec.h"
#include "shellmisc.h"
#include "paraexec.h"
#include "builtincmd.h"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        // interactive mode
        while (1) {
            /* printf("PATH_NUM: %d\n", PATH_NUM); */
            /* for (int i=0; i<PATH_NUM; i++) */
            /*     printf("%s ", path[i]); */
            /* printf("\n"); */
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
                for (int i=0; i<1+strlen(line); i++)
                    usrline[i] = '\0';
                usrline[0] = c;
                strcat(usrline,line);

                /* printf("usrline generated\n"); */

                //extract command from usrline
                int* cmdnum = malloc(sizeof(int));
                *cmdnum = 0;
                struct cmdent* cmdblk = extract(usrline, cmdnum);

                /* printf("line 47 path[0]: %s\n", path[0]); */
                /* printf("line 47 path[0]: %s\n", path); */

                // build in command: exit
                /* if (!strcmp(cmdblk[0].args[0],"exit")) { */
                /*     /1* printf("compare command: %s with exit\n", cmdblk[0].args[0]); *1/ */
                /*     exit(0); */
                /* } */
                
                //check if command exists in directories and is executable
                // execute commands parallelly
                paraexec(cmdblk, cmdnum);
                /* printf("finished executing commands\n"); */
                /* if (*retval == -1) { */
                /*     write(STDERR_FILENO, error_message, strlen(error_message)); */
                /* } */
                /* printf("retval: %d\n", *retval); */
                // after finishing all commands, free memory of cmdblk and retval
            free(line);
            /* free(usrline); */
            /* free(cmdnum); */
            /* free(cmdblk); */
            } else if (c == EOF) {
                // if user input EOF, exit program gracefully
                printf("\n");
                exit(0);
            }
        }
    }
    return 0;
}
