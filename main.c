#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char upper_filter(char c) {
    if(c > 96 & c < 123) {
        c -= 32;
    }
    return c;
}

char lower_filter(char c) {
    if(c > 64 & c < 91) {
        c += 32;
    }
    return c;
}

char null_filter(char c) {
    return c;
}

char* transform(char *c, char (*transformation)(char)) {
    for (int i = 0; i < sizeof(c); i++) {
        c[i] = transformation(c[i]);
    }

    return c;
}

int main(int argc, char *argv[]) {

    int chara;
    char *input_file;
    char *output_file;
    char *result;
    char (*transform_func)(char);

    while ((chara = getopt (argc, argv, "i:o:f:")) != -1) {
        switch (chara) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
            case 'f':
                result = optarg;
                if (strcmp(result, "upper") == 0)  {
                    transform_func = upper_filter;
                } else if(strcmp(result, "lower") == 0) {
                    transform_func = lower_filter;
                } else {
                    transform_func = null_filter;
                }
                break;
            default:
                NULL;
        }
    }

    int fd = open(input_file, O_RDONLY | O_CREAT);
    int fd2 = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char* c = (char*)calloc(1, sizeof(char));

    int count = 0;
    ssize_t sz;
    while((sz = read(fd, c, 1)) > 0) {
        c = transform(c, transform_func);
        ssize_t sz2 = write(fd2, c, 1);
    }

    if (close(fd) < 0) {
        perror("c1");
        exit(1);
    }

    if (close(fd2) < 0) {
        perror("c1");
        exit(1);
    }

    free(c);
    return 0;
}
