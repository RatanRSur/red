#include <stdio.h>
#include <string.h>
#include "utils.c"
#include <stdint.h>
#include <unistd.h>

int64_t sum_from_fileptr(FILE *fp) {
    int64_t sum = 0;

    while (!feof(fp)) {
        int64_t current;
        fscanf(fp, "%lld ", &current);
        sum += current;
    }

    return sum;
}

int64_t sum_from_filename(char *filename) {
    FILE *fp = fopen(filename, "r");
    int64_t sum = sum_from_fileptr(fp);
    fclose(fp);
    return sum;
}

int64_t prod_from_fileptr(FILE *fp) {
    int64_t prod = 1;

    while (!feof(fp)) {
        int64_t current;
        fscanf(fp, "%lld ", &current);
        prod *= current;
    }

    return prod;
}

int64_t prod_from_filename(char *filename) {
    FILE *fp = fopen(filename, "r");
    int64_t prod = prod_from_fileptr(fp);
    fclose(fp);
    return prod;
}

int main(int argc, char **argv) {
    char mode = 's';
    int c;

    while ((c = getopt(argc, argv, "sp")) != -1) {
        mode = (char) c;
    }

    int64_t accumulator;

    switch (mode) {
    case 's':
        accumulator = 0;
        break;

    case 'p':
        accumulator = 1;
        break;
    }

    for (int i = optind; i < argc; ++i) {
        char *filename = (char *) calloc(strlen(argv[i]) + 1, 1);
        exit_if_null(filename);
        strcpy(filename, argv[i]);

        switch (mode) {
        case 's':
            accumulator += sum_from_filename(filename);
            break;

        case 'p':
            accumulator *= prod_from_filename(filename);
            break;
        }

        free(filename);
    }

    printf("%lld", accumulator);
    printf("\n");
    return 0;
}
