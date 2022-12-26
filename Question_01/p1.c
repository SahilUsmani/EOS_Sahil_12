#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int fd_file = 0; // file descriptor for opening file
    int fd_fifo = 0; // file descriptor for opening fifo
    int read_file = 0;// ret value for read file
    int write_fifo = 0;// ret value for write fifo
    int cls_ret_file = 0;// ret value  for close file
    int cls_ret_fifo = 0;// ret value for close fifo
    //char buff[10000];
    char buff;

    fd_file = open("/usr/include/stdio.h", O_RDONLY);

    if (fd_file == -1) { // error handling for file opening
        perror("File Opening Error");
        exit(EXIT_FAILURE);
    }
    
    fd_fifo = open("sahilfifo", O_WRONLY);

    if (fd_fifo == -1) {// error handling for fifo opening
        perror("Fifo Opening Error");
        exit(EXIT_FAILURE);
    }

    /*read_file = read(fd_file, buff, 2048);
    if (read_file == -1) {
        perror("Read File Error");
        exit(EXIT_FAILURE);
    }

    write_fifo = write(fd_fifo, buff, 2048);
    if (write_fifo == -1) {
        perror("Write Fifo Error");
        exit(EXIT_FAILURE);
    }*/

    while(read(fd_file, &buff, 1))
    {
        write(fd_fifo, &buff, 1);
    }


    
    printf("the size of buff is :: %ld\n", strlen(&buff));
   // printf("the size of buff_fifo is :: %ld\n", strlen(buff_fifo));
    
    
    cls_ret_file = close(fd_file);

    if (cls_ret_file == -1) { // error handling for closing of file
        perror("File CLosing Error");
        exit(EXIT_FAILURE);
    }

    cls_ret_fifo = close(fd_fifo);

    if (cls_ret_fifo == -1) { // error handling for closing of fifo
        perror("Fifo CLosing Error");
        exit(EXIT_FAILURE);
    }
    return 0;


}