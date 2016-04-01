#include <string.h>
#include <stdlib.h>

#define exit_if_null(ptr)\
    if (NULL == ptr){\
        printf("%s was NULL", #ptr);\
        exit(1);\
    }
