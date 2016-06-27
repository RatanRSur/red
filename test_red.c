#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "utils.c"

#define run_test(fn_name)\
    printf("%s\n", #fn_name);\
    fn_name();

char red_binary[] = "./bin/red";

char *call_and_write_to_red(char *const *args, const char *input) {
    int write_pipe[2];
    int read_pipe[2];
    pipe(write_pipe);
    pipe(read_pipe);
    char buf[100];
    pid_t pid = fork();

    if (pid) {
        close(write_pipe[0]);
        close(read_pipe[1]);
        write(write_pipe[1], input, strlen(input) + 1);
        close(write_pipe[1]);
        read(read_pipe[0], buf, 10);
        close(read_pipe[0]);
    } else {
        close(write_pipe[1]);
        close(read_pipe[0]);
        dup2(read_pipe[1], 1);
        dup2(write_pipe[0], 0);
        execvp(red_binary, args);
        exit(0);
    }

    char *result = (char *) calloc(strlen(buf) + 1, sizeof(char));
    strcpy(result,buf);
    return result;
}

char *call_red(char *const *args) {
    return call_and_write_to_red(args, "");
}

void test_nothing_w_no_args() {
    char *const args[] = {red_binary, NULL};
    char *result = call_red(args);
    assert(0 == strcmp(result, "0\n"));
    free(result);
}

void test_one_int() {
    char *const args[] = {red_binary, "test_files/one_int.txt", NULL};
    char *result = call_red(args);
    assert(0 == strcmp(result , "1\n"));
    free(result);
}

void test_two_ints() {
    char *const args[] = {red_binary, "test_files/two_ints.txt", NULL};
    char *result = call_red(args);
    assert(0 == strcmp(result , "7\n"));
    free(result);
}

void test_five_ints() {
    char *const args[] = {red_binary, "test_files/five_ints.txt", NULL};
    char *result = call_red(args);
    assert(0 == strcmp(result , "15\n"));
    free(result);
}

void test_funky_line_breaks() {
    char *const args[] = {red_binary, "test_files/funky_line_breaks.txt", NULL};
    char *result = call_red(args);
    assert(0 == strcmp(result , "30\n"));
    free(result);
}

void test_empty_file() {
    char *const args[] = {red_binary, "test_files/empty.txt", NULL};
    char *result = call_red(args);
    assert(0 == strcmp(result , "0\n"));
    free(result);
}

void test_large_ints() {
    char *const args[] = {red_binary, "test_files/large_ints.txt", NULL};
    char *result = call_red(args);
    assert(0 == strcmp(result , "5000000000\n"));
    free(result);
}

void test_negative_ints() {
    char *const args[] = {red_binary, "test_files/negative_ints.txt", NULL};
    char *result = call_red(args);
    assert(0 == strcmp(result , "-9\n"));
    free(result);
}

void test_two_files() {
    char *const args[] = {red_binary, "test_files/file1.txt", "test_files/file2.txt", NULL};
    char *result = call_red(args);
    assert(0 == strcmp(result , "0\n"));
    free(result);
}

void test_product_option() {
    char *const args[] = {red_binary, "-p", "test_files/five_ints.txt", NULL};
    char *result = call_red(args);
    assert(0 == strcmp(result , "120\n"));
    free(result);
}

/*void test_one_line_from_stdin() {*/
/*char *const args[] = "test_files/five_ints.txt";*/
/*char *result = call_and_write_to_red(args,"42\n");*/
/*assert(0 == strcmp(result , "42\n"));*/
/*free(result);*/
/*}*/

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
    /*run_test(test_one_line_from_stdin);*/
    printf("%sPassing.%s\n", "\x1B[32m", "\x1B[0m");
    return 0;
}
