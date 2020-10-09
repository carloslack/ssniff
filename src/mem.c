/*
 * mem.c
 *
 * Performs memory allocation/deallocation
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "int.h"
#include "mem.h"

#ifndef lint
static const char rcsid[] = "$Id$";
#endif /* lint */

void* m_alloc(size_t n, void (*errf)(int))
{ 
    void *p = malloc(n);

    if(n == 0 || p == NULL)
    {
        errno = (!n) ? EINVAL : ENOMEM;
        perror("m_alloc");
        if(errf) errf(EXIT_FAILURE);
        return NULL;
    }

    return p;
}

void* c_alloc(size_t n, size_t m, void (*errf)(int))
{
    void *p = NULL;
    errno = 0;

    if(mul_ui(n, m, NULL) != INT_OK)
        errno = EOVERFLOW;

    p = calloc(n,m);

    if(n == 0 || p == NULL)
        errno = (!n) ? EINVAL : ENOMEM;

    if(errno)
    {
        perror("c_alloc");
        if(errf) errf(EXIT_FAILURE);
        return NULL;
    }

    return p;
}

void m_free(void **ptr)
{
    if(ptr)
        free(*ptr),
            *ptr = NULL;
}

void s_free(void **ptr, size_t n)
{
    if(ptr && *ptr)
        memset(*ptr, 0x0, n);
    m_free(ptr);
}

