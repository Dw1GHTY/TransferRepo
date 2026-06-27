#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>


#define BUF_SIZE 2


int number_buffer[BUF_SIZE];
int write_interval;

void* generate_numbers(void* args)
{
    int x,y;
    x = rand() % 11;
    y = rand() % 11;
}

int main(int argc, char* argv[])
{
    write_interval = rand() % 5;

    return 0;
}