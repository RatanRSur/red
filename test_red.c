#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "utils.c"

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
    exit_if_null(fp);

    char *lineptr = NULL;
    size_t len = 0;
    getline(&lineptr, &len, fp);
    pclose(fp);
    return lineptr;
}

void test_nothing_w_no_args() {
    char args[] = "";
    assert(0 == strcmp(call_red(args, strlen(args)), "\n"));
}

void test_returns_one_int_one(){
    char args[] = "test_files/one_int_one.txt";
    assert(0 == strcmp(call_red(args, strlen(args)), "1\n"));
}

int main() {
    run_test(test_nothing_w_no_args);
    run_test(test_returns_one_int_one);
    printf("%sPassing.%s\n", "\x1B[32m", "\x1B[0m");
    return 0;
}
