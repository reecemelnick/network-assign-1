#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int const LOWERCASE_MIN = 96;
int const LOWERCASE_MAX = 123;
int const DISTANCE_TO_OTHER = 32;
int const UPPERCASE_MIN = 64;
int const UPPERCASE_MAX = 91;

char upper_filter(char c) {
    if(c > LOWERCASE_MIN & c < LOWERCASE_MAX) {
        c -= 32;
    }
    return c;
}

char lower_filter(char c) {
    if(c > UPPERCASE_MIN & c < UPPERCASE_MAX) {
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

char** parse_args(int argc, char** argv) {
    int chara;
    char *input_file;
    char *output_file;
    char *result;
    char (*transform_func)(char);
    char** results = (char**)malloc(sizeof(char*) * 3);
    results[0] = (char*)malloc(sizeof(argv[0]));
    results[1] = (char*)malloc(sizeof(argv[1]));
    results[2] = (char*)malloc(sizeof(argv[3]));

    while ((chara = getopt (argc, argv, "i:o:f:")) != -1) {
        switch (chara) {
            case 'i':
                input_file = optarg;
                results[0] = input_file;
                break;
            case 'o':
                output_file = optarg;
                results[1] = output_file;
            case 'f':
                result = optarg;
                if (strcmp(result, "upper") == 0) {
                    transform_func = upper_filter;
                } else if (strcmp(result, "lower") == 0) {
                    transform_func = lower_filter;
                } else {
                    transform_func = null_filter;
                }
                results[2] = result;
                break;
            default:
                NULL;
        }
    }

    return results;
}



int main(int argc, char *argv[]) {

    int chara;
    char *input_file;
    char *output_file;
    char *result;
    char (*transform_func)(char);

//    char** argument_strings = parse_args(argc, argv);
//    input_file = argument_strings[0];
//    output_file = argument_strings[1];

//    printf("arg 1: %s", argument_strings[0]);

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
//        c = transform(c, upper_filter);
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
