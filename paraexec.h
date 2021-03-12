#ifndef PARAEXEC_H
#define PARAEXEC_H

#include <stdlib.h>
#include <stdio.h>
#include "shellmisc.h"

// given a set of commands, execute them parallelly
// cmdblk stores a set of commands that are about to execute
// cmdnum stores the total commands that are about to execute
// retval stores the return value
void paraexec(struct cmdent* cmdblk, int *cmdnum); 

#endif
