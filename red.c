#include <stdio.h>
#include <string.h>
#include "utils.c"
#include <stdint.h>

int64_t sum_from_fileptr(FILE *fp) {
    int64_t sum = 0;

    while (!feof(fp)) {
        int64_t current;
        fscanf(fp, "%lld ", &current);
        sum += current;
    }

    return sum;
}

uint64_t sum_from_filename(char *filename) {
    FILE *fp = fopen(filename, "r");
    int64_t sum = sum_from_fileptr(fp);
    fclose(fp);
    return sum;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        int64_t sum = 0;

        for (int i = 1; i < argc; ++i) {
            char *filename = (char *) calloc(strlen(argv[i]) + 1, 1);
            exit_if_null(filename);
            strcpy(filename, argv[i]);
            sum += sum_from_filename(filename);
            free(filename);
        }

        printf("%lld", sum);
    }

    printf("\n");
    return 0;
}
