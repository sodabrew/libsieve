
/* Flex helper functions. */

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"

int libsieve_lexinput(char **ptr, size_t *ptr_len, char *buf, int max)
{
    size_t n, max_size = (size_t)max;

    if (ptr == NULL || *ptr == NULL)
        return 0;

    if ((n = *ptr_len < max_size ? *ptr_len : max_size) <= 0)
        return 0;

    memcpy(buf, *ptr, n);
    *ptr += n;
    *ptr_len -= n;

    return n;
}

