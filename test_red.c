#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "utils.c"

#define run_test(fn_name)\
    printf("%s\n", #fn_name);\
    fn_name();

char *call_and_write_to_red(char *args, char *input) {
    int write_pipe[2];
    int read_pipe[2];
    pipe(write_pipe);
    pipe(read_pipe);
    pid_t pid = fork();
    char buf[100];

    if (pid) {
        close(write_pipe[0]);
        close(read_pipe[1]);
        write(write_pipe[1], input, strlen(input) + 1);
        close(write_pipe[1]);
        read(read_pipe[0], buf, 10);
        close(read_pipe[0]);
    } else {
        fputs("beginning of child\n", stderr);
        close(write_pipe[1]);
        close(read_pipe[0]);
        dup2(write_pipe[0], 0);
        dup2(read_pipe[1], 1);
        char bin[] = "./bin/red ";
        char *command = (char *) calloc(strlen(bin) + strlen(args) + 1, sizeof(char));
        strcpy(command, bin);
        strcat(command, args);
        execlp(command, bin, (char *) NULL);
        free(command);
        fputs("end of child\n", stderr);
        exit(0);
    }
    fputs("end of both\n", stderr);

    int result_length = 1;
    char *c = buf;
    while(*c != '\n') {
        ++c;
        fprintf(stderr, "%c\n", *c);
    }
    ++c;
    *c = '\0';

    char *result = (char *) calloc(result_length + 1, sizeof(char));
    strcpy(buf, result);
    return result;
}

char *call_red(char *args) {
    return call_and_write_to_red(args, "");
}

void test_nothing_w_no_args() {
    char args[] = "";
    char *result = call_red(args);
    assert(0 == strcmp(result, "0\n"));
    free(result);
}

void test_one_int() {
    char args[] = "test_files/one_int.txt";
    char *result = call_red(args);
    assert(0 == strcmp(result , "1\n"));
    free(result);
}

void test_two_ints() {
    char args[] = "test_files/two_ints.txt";
    char *result = call_red(args);
    assert(0 == strcmp(result , "7\n"));
    free(result);
}

void test_five_ints() {
    char args[] = "test_files/five_ints.txt";
    char *result = call_red(args);
    assert(0 == strcmp(result , "15\n"));
    free(result);
}

void test_funky_line_breaks() {
    char args[] = "test_files/funky_line_breaks.txt";
    char *result = call_red(args);
    assert(0 == strcmp(result , "30\n"));
    free(result);
}

void test_empty_file() {
    char args[] = "test_files/empty.txt";
    char *result = call_red(args);
    assert(0 == strcmp(result , "0\n"));
    free(result);
}

void test_large_ints() {
    char args[] = "test_files/large_ints.txt";
    char *result = call_red(args);
    assert(0 == strcmp(result , "5000000000\n"));
    free(result);
}

void test_negative_ints() {
    char args[] = "test_files/negative_ints.txt";
    char *result = call_red(args);
    assert(0 == strcmp(result , "-9\n"));
    free(result);
}

void test_two_files() {
    char args[] = "test_files/file1.txt test_files/file2.txt";
    char *result = call_red(args);
    assert(0 == strcmp(result , "0\n"));
    free(result);
}

void test_product_option() {
    char args[] = "-p test_files/five_ints.txt";
    char *result = call_red(args);
    assert(0 == strcmp(result , "120\n"));
    free(result);
}

/*void test_one_line_from_stdin() {*/
/*char args[] = "test_files/five_ints.txt";*/
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
