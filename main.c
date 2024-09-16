#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int fd = open(argv[1], O_RDONLY | O_CREAT);

    char* c = (char*)calloc(100, sizeof(char));

    int sz = read(fd, c, 50);

    printf("fd = %d\n", fd);
    printf("Read returned %d\n", sz);
    printf("Buffer: %s\n", c);

    if (close(fd) < 0) {
        perror("c1");
        exit(1);
    }
    printf("closed the fd.\n");

    free(c);


    return 0;
}
