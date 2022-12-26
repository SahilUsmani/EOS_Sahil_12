/* Process P1 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h> 
#include <string.h>

char *count_s;
int main()
{
    int shm_desc = 0; // shared memory descriptor
    int ftr_err = 0; // ret value for ftruncate
    int fd_file = 0;// file descriptor
    int read_file = 0;// ret value for reading the file
    char buff[2048];

    /*
    This is the API for creating or opening shared memory objects.

    int shm_open(const char *name, int oflag, mode_t mode);

        - Here, 1st argument is "/name_of_shared_memory_object"
            ()
    */

    fd_file = open("/usr/include/stdio.h", O_RDONLY);
    if (fd_file == -1) { // error handling for file opening
        perror("File Opening Error");
        exit(EXIT_FAILURE);
    }

    read_file = read(fd_file, buff, strlen(buff));
    if (read_file == -1) {// error handling for read file
        perror("Read File Error");
        exit(EXIT_FAILURE);
    }

    shm_desc = shm_open("/sahilshm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shm_desc == -1) { // error handling for opening and creating shared memory
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    ftr_err = ftruncate(shm_desc, sizeof(buff));
    if (ftr_err == -1) { // error handling for ftruncate
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    /*
    void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

    */
    count_s = (char *)mmap(NULL, sizeof(buff), PROT_READ | PROT_WRITE, MAP_SHARED, shm_desc, 0);
    *count_s = buff[2048];
    return 0;
}