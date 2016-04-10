#include <stdio.h>
#include <string.h>
#include "utils.c"
#include <stdint.h>

int main(int argc, char **argv) {
    if (2 == argc) {
        // open file if supplied as argument
        char *filename = (char *) calloc(strlen(argv[1]) + 1, 1);
        exit_if_null(filename);
        strcpy(filename, argv[1]);
        FILE *fp = fopen(filename, "r");
        free(filename);
        int64_t sum = 0;

        while (!feof(fp)) {
            int64_t current;
            fscanf(fp, "%lld ", &current);
            sum += current;
        }

        fclose(fp);
        printf("%lld", sum);
    }

    printf("\n");
    return 0;
}
