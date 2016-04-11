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
    char *command = (char *) calloc(strlen(bin) + arglen + 1, sizeof(char));
    strcpy(command, bin);
    strcat(command, args);
    FILE *fp;
    fp = popen(command, "r");
    free(command);
    exit_if_null(fp);
    char *line = NULL;
    size_t len = 0;
    getline(&line, &len, fp);
    pclose(fp);
    return line;
}

void test_nothing_w_no_args() {
    char args[] = "";
    char *result = call_red(args, strlen(args));
    assert(0 == strcmp(result, "0\n"));
    free(result);
}

void test_one_int() {
    char args[] = "test_files/one_int.txt";
    char *result = call_red(args, strlen(args));
    assert(0 == strcmp(result , "1\n"));
    free(result);
}

void test_two_ints() {
    char args[] = "test_files/two_ints.txt";
    char *result = call_red(args, strlen(args));
    assert(0 == strcmp(result , "7\n"));
    free(result);
}

void test_five_ints() {
    char args[] = "test_files/five_ints.txt";
    char *result = call_red(args, strlen(args));
    assert(0 == strcmp(result , "15\n"));
    free(result);
}

void test_funky_line_breaks() {
    char args[] = "test_files/funky_line_breaks.txt";
    char *result = call_red(args, strlen(args));
    assert(0 == strcmp(result , "30\n"));
    free(result);
}

void test_empty_file() {
    char args[] = "test_files/empty.txt";
    char *result = call_red(args, strlen(args));
    assert(0 == strcmp(result , "0\n"));
    free(result);
}

void test_large_ints() {
    char args[] = "test_files/large_ints.txt";
    char *result = call_red(args, strlen(args));
    assert(0 == strcmp(result , "5000000000\n"));
    free(result);
}

void test_negative_ints() {
    char args[] = "test_files/negative_ints.txt";
    char *result = call_red(args, strlen(args));
    assert(0 == strcmp(result , "-9\n"));
    free(result);
}

void test_two_files() {
    char args[] = "test_files/file1.txt test_files/file2.txt";
    char *result = call_red(args, strlen(args));
    assert(0 == strcmp(result , "0\n"));
    free(result);
}

void test_product_option() {
    char args[] = "-p test_files/five_ints.txt";
    char *result = call_red(args, strlen(args));
    assert(0 == strcmp(result , "120\n"));
    free(result);
}

int main() {
    run_test(test_nothing_w_no_args);
    run_test(test_one_int);
    run_test(test_two_ints);
    run_test(test_five_ints);
    run_test(test_funky_line_breaks);
    run_test(test_empty_file);
    run_test(test_large_ints);
    run_test(test_negative_ints);
    run_test(test_two_files);
    run_test(test_product_option);
    printf("%sPassing.%s\n", "\x1B[32m", "\x1B[0m");
    return 0;
}
