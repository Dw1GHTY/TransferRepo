#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;
    if ((dp = opendir("test")) == NULL)
    {
        printf("Ne moze se otvoriti direktorijum");
        exit(1);
    }
    while ((dirp = readdir(dp)) != NULL)
        printf("%s\n", dirp->d_name);
    rewinddir(dirp);
    closedir(dp);
}