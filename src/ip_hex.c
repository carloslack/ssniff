/*
 * ip_hex.c
 *
 * Dump packet buffer in hexdump-like format
 */

#include <stdio.h>
#include <ctype.h>

#define DUMPLEN 16

static void _hexdump(unsigned char * data, size_t len)
{
    /*
    * Copyright (C) 1998  Mark Baysinger (mbaysing@ucsd.edu)
    * Copyright (C) 1998,1999  Ross Combs (rocombs@cs.nmsu.edu)
    */
    unsigned int i;
    size_t r,c;

    if (!data)
        return;

    for (r=0,i=0; r<(len/16+(len%16!=0)); r++,i+=16)
    {
        printf("\t%04X:   ",i); /* location of first byte in line */

        for (c=i; c<i+8; c++) /* left half of hex dump */
            if (c<len)
                printf("%02X ",((unsigned char const *)data)[c]);
            else
                printf("   "); /* pad if short line */

        printf("  ");

        for (c=i+8; c<i+16; c++) /* right half of hex dump */
            if (c<len)
                printf("%02X ",((unsigned char const *)data)[c]);
            else
                printf("   "); /* pad if short line */

        printf("   ");

        for (c=i; c<i+16; c++) /* ASCII dump */
            if (c<len)
                if (((unsigned char const *)data)[c]>=32 &&
                        ((unsigned char const *)data)[c]<127)
                    printf("%c",((char const *)data)[c]);
                else
                    printf("."); /* put this for non-printables */
            else
                printf(" "); /* pad if short line */

        printf("\n");
    }
}

void ssniff_payload(char *buff, int len)
{
    _hexdump((unsigned char*)buff, len);
}

