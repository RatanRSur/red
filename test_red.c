#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define run_test(fn_name)\
    printf("%s\n", #fn_name);\
    fn_name();

void run_red(char *args, int arglen) {

    char exe[] = "./bin/red";
    char *command = (char*) calloc(sizeof(exe) + arglen, 1);
    strcpy(command, exe);
    strcat(command, args);
    FILE *fp;
    fp = popen(command, "r");

    /*if (NULL == fp) {*/
        /*printf("failure");*/
        /*exit(1);*/
    /*}*/

    pclose(fp);
}

int main() {
    return 0;
}
