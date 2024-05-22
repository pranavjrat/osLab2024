#include<stdio.h>
#include<unistd.h>



int main(void)
{
printf("Here I am just before first forking statement\n");
fork( );
printf("Here I am just after first forking statement\n");
fork( );
printf("Here I am just after second forking statement\n");
fork( );
printf("Here I am just after third forking statement\n");
printf(" Hello World from process %d!\n", getpid( ));
}
