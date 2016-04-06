#include <stdio.h>
#include <string.h>
#include "utils.c"

int main(int argc, char **argv) {
    if (2 == argc) {
        // open file if supplied as argument
        char *filename = (char *) calloc(strlen(argv[1]) + 1, 1);
        exit_if_null(filename);
        strcpy(filename, argv[1]);
        FILE *fp = fopen(filename, "r");
        free(filename);
        int sum = fscanf(fp, "%d ", &sum);

        while (!feof(fp)) {
            sum += fscanf(fp, "%d ", &sum);
        }

        fclose(fp);
        printf("%d", sum);
    }

    printf("\n");
    return 0;
}