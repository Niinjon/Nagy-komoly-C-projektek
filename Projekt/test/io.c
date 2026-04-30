#include <stdio.h>
#include <stdlib.h>

int file_exists(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f) {
        fclose(f);
        return 1;
    }
    return 0;
}

int write_file(const char *filename, const char *content) {

    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("fopen");
        return 0;
    }

    fputs(content, f);
    fclose(f);
    return 1;
}