/*
 * mem.h
 */

#ifndef _MEM_H
#define _MEM_H

void*   m_alloc (size_t, void (*)(int));
void*   c_alloc (size_t, size_t, void (*)(int));
void    s_free  (void **, size_t);
void    m_free  (void **);

#else
#endif
