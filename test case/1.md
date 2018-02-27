```
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

static char *output;
#define SIZE 512
#define FRAME_SIZE 10

void signal_process(int sig_id)
{
        void *array[FRAME_SIZE];
        size_t size;
        char **strings;
        size_t i;
        int fd;
        char tmp[SIZE] = {0};
        size = backtrace(array, FRAME_SIZE);
        strings = backtrace_symbols(array, size);
        fd = open(output, O_RDWR|O_CREAT, 0644);
        sprintf(tmp, "Obtained %zd stack frames.\n", size);
        write(fd, tmp, SIZE);
        for (i = 0; i < size; i++) {
                memset(tmp, '\0', SIZE);
                sprintf(tmp, "%s\n", strings[i]);
                write(fd, tmp, SIZE);
        }
        close(fd);
        free(strings);
}

void call3()
{
        volatile unsigned int i;
        char tmp[2048];
        char tmp1[2048] = {0};

        i = 0;
        i++;
        memcpy(tmp, tmp1, 2048);
}

void call2()
{
        call3();
}

void call1()
{
        call2();
}

int main(int argc, char *argv[])
{
        if (argc < 2) {
                printf("Error, need add one arg about output log!\n");
                exit(1);
        }
        output = argv[1];
        signal(SIGALRM, signal_process);
        call1();
        return 0;
}

```
