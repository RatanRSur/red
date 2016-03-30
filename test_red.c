#include <stdlib.h>
#include <stdio.h>

#define run_test(fn_name)\
    printf("%s\n", #fn_name);\
    fn_name();

void run_red(char *args, int arglen) {

    char exe[] = "./bin/red";
    char *command = (char*) malloc(sizeof(exe) + arglen);
    strcpy(command, exe);
    strcat(command, )
    /*FILE *fp;*/
    /*fp = popen("./bin/red", "r");*/

    /*if (NULL == fp) {*/
        /*printf("failure");*/
        /*exit(1);*/
    /*}*/

    /*pclose(fp);*/
}

int main() {
    return 0;
}
