/* Process P2 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <string.h> 

//char count_r;
int main()
{
    int shm_desc = 0; // shared memory descriptor
    int ftr_err = 0; // ret value for ftruncate
    char buff[2048];
    int count = 0;// for counting the occurrence

    
    shm_desc = shm_open("/desdshm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shm_desc == -1) { //error handling for opening and creating the shared memory
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    ftr_err = ftruncate(shm_desc, sizeof(buff));
    if (ftr_err == -1) { //error handling for ftruncate
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    /*
    void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

    */
    buff[2048] = (char *)mmap(NULL, sizeof(buff), PROT_READ | PROT_WRITE, MAP_SHARED, shm_desc, 0);

    // calculating the occurrence of letter 's'
    for(int i=0; i<=2047; i++) {
        if (buff[i] == 's') {
            count++;
        }
    }
    
    printf("The occurrence of the character s is :: %d\n", count);

    return 0;
}