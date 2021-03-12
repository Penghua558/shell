# shell
a project which implements a shell for UNIX based operating systems <br/>
project source url: https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/processes-shell <br/>

# What can this shell do?
* can execute most of shell commands, such as ``ls``, ``cat``, etc, I didn't test 
much shell commands 
* support parallel command, which is achieved by using symbol ``&``
* has 3 built-in commands, ``exit``, ``cd`` and ``path``, type ``exit`` to exit the 
shell program, use ``cd`` to navigate between directories like you normally do in 
common shell, 
use ``path`` to overwrite the default path enviroment of the shell, detailed usage 
of ``path`` will be explained below

## ``path`` built-in command and default path enviroment
The default path enviroment of the shell is:

    /bin, /sbin, /usr/bin.
So most common shell commands should work normally without telling you that program 
can't find the executables.<br/>
To change default path enviroment, use following syntax:

    path <path1> <path2> <path3> ...
executing this command should overwrite current path enviroment with new  paths 
``path1``,``path2``, ``path3`` and whatever paths you have passed on the command. If you
only type a single command ``path`` without passing any argument, nothing will happen to 
path enviroment, instead an error message will print to screen.
