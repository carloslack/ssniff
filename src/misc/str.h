/*
 * str.h
 */

#ifndef _STR_H
#define _STR_H

int     strcnt  (const char *, char);
char    **strsplt (const char *, char);
size_t  strlcat (char *, const char *, size_t);
size_t  strlcpy (char *, const char *, size_t);

#endif
