#include <unistd.h>
#include <stdlib.h>
void daemonize(const char* cmd);


int main()
{
	daemonize("main");
	while(1) sleep(1);
}
