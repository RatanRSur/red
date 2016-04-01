#include <stdio.h>
#include <string.h>
#include "utils.c"

int main(int argc, char **argv){
    char *filename = (char*) calloc(strlen(argv[1]) + 1, 1);
    exit_if_null(filename);
    strcpy(filename, argv[1]);
    FILE *fp = fopen(filename, "r");
    fclose(fp);
    printf("\n");
    return 0;
}
