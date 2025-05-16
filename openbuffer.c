/*
Practicing file opening/buffering more low-level

Idea is that using 'POSIX' calls instead of C api, we
can control exactly the buffers.
*/

#include <fcntl.h> // open()
#include <unistd.h> // r, w, close()
#include <stdio.h>
#include <stdint.h>


#define BUFF_SIZE 1024

int main() {
    int fd = open("data/tmp.csv",O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    uint8_t buff[BUFF_SIZE];

    

    // read a buff
    read(fd,buff,BUFF_SIZE);

    printf("%s\n",buff);

    close(fd);

}