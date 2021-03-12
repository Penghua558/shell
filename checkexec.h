#ifndef CHECKEXEC_H
#define CHECKEXEC_H

#include <stdlib.h>
#include <stdio.h>

// check if cmd is accessible and executable
// if cmd exists and is executable, the  function will return 0 and pass full path of cmd into
// pathname, otherwise return -1
char* check(char* cmd);
#endif
