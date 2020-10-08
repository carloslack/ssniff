/*
 * str.c
 *
 * Performs string manipulation
 *
 */

#include <string.h>
#include <stdlib.h>

#include "mem.h"
#include "str.h"

#ifndef lint
static const char rcsid[] = "$Id$";
#endif /* lint */

int strcnt(const char *p, char c) 
{
	const char  *q = p;
    int         n = 0;

    if(!p) return -1;

    while( (q = strchr(q, c)) != NULL)
        n++, q++;
    return n;
}

char **strsplt(const char *ptr, char c)
{
    char            *q, *t, *p;
    unsigned int    k, i = 0;
    char            **toks;

    if(!ptr || (k = strcnt(ptr, c)) < 0)
        return NULL;

    if(k == 0) 
	{
        toks = malloc(sizeof(char*));
        *toks = strdup(ptr);
        return toks;
    }

    p = strdup(ptr);
    toks = m_alloc((k+1)*sizeof(char*), NULL);
    if(!p || !toks)
        return NULL;

    for(q=t=p; q && *q != '\0'; q++)
	{
        if(*q == c)
		{
         	*q = '\0'; k = strlen(t);
            *(toks+i) = m_alloc(k+1, exit);
            strlcpy((*toks+i++), t, k+1);
            t = q+1;
        } 
		else if(*(q+1) == '\0') 
		{
            k = strlen(t);
            *(toks+i) = m_alloc(k+1, exit);
            strlcpy(*(toks+i++), t, k+1);
        }
    }
    m_free((void*)&p);
    return toks;
}

/* Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com> */
size_t
strlcat(char *dst, const char *src, size_t siz){
    char        *d = dst;
    const char  *s = src;
    size_t      n = siz;
    size_t      dlen;

    while(n-- != 0 && *d != '\0')
        d++;
    dlen = d - dst;
    n = siz - dlen;

    if(n == 0)
        return(dlen + strlen(s));

    while(*s != '\0')
	{
     	if(n != 1)
		{
            *d++ = *s;
            n--;
        }
        s++;
    }
    *d = '\0';
    return(dlen + (s - src));
}

/* Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com> */
size_t
strlcpy(char *dst, const char *src, size_t siz)
{
	char        *d = dst;
    const char  *s = src;
    size_t      n = siz;

    if(n != 0)
	{
        while(--n != 0)
		{
            if ((*d++ = *s++) == '\0')
                break;
        }
    }

    if (n == 0)
	{
        if(siz != 0)
            *d = '\0';

        while(*s++);
    }

    return(s - src - 1);
}
