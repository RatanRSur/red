#include <stdio.h>
#include <string.h>
#include "utils.c"
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        int64_t sum = 0;

        for (int i = 1; i < argc; ++i) {
            char *filename = (char *) calloc(strlen(argv[i]) + 1, 1);
            exit_if_null(filename);
            strcpy(filename, argv[i]);
            FILE *fp = fopen(filename, "r");
            free(filename);

            while (!feof(fp)) {
                int64_t current;
                fscanf(fp, "%lld ", &current);
                sum += current;
            }

            fclose(fp);
        }

        printf("%lld", sum);
    }

    printf("\n");
    return 0;
}
