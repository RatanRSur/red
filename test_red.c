#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define run_test(fn_name)\
    printf("%s\n", #fn_name);\
    fn_name();


char *call_red(char *args, int arglen) {
    char bin[] = "./bin/red ";
    char *command = (char *) calloc(sizeof(bin) + arglen, sizeof(char));
    strcpy(command, bin);
    strcat(command, args);
    FILE *fp;
    fp = popen(command, "r");
    free(command);

    if (NULL == fp) {
        printf("failure");
        exit(1);
    }

    printf("\tArgs: %s\n", args);
    char *lineptr = NULL;
    size_t len = 0;
    getline(&lineptr, &len, fp);
    pclose(fp);
    return lineptr;
}

void test_bin_exists() {
    assert(0 == strcmp(call_red("", 0), ""));
}

int main() {
    run_test(test_bin_exists);
    printf("%sPassing.%s\n", "\x1B[32m", "\x1B[0m");
    return 0;
}
