#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void bye(void)
{
	printf("bye\n");
}

int main(int argc,char ** argv)
{
	atexit(bye);
}
