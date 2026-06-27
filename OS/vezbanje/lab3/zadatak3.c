#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/file.h>

char path_to_executable[100];
char path_to_file[100];

int main(int argc, char* argv[])
{
    int fd;

    fd = open(argv[2], O_CREAT | O_TRUNC | O_RDWR, 0777);

    dup2(fd, 1);

    close(fd);


    execlp(argv[1], argv[1], NULL);


    return 0;
}