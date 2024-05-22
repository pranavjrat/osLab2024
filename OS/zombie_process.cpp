#include <stdio.h>
#include <unistd.h>
main ( )
{
 execl ("/bin/ls", /* program to run - give full path */
 "ls", /* name of program sent to argv[0] */
 "-l", /* first parameter (argv[1])*/
 "-a", /* second parameter (argv[2]) */
 NULL) ; /* terminate arg list */

 printf ("EXEC Failed\n") ;
 /* This above line will be printed only on error and not otherwise */
} 