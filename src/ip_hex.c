/*
 * ip_hex.c
 *
 * Dump packet buffer in hexdump-like format
 */

#include <stdio.h>
#include <ctype.h>

#define DUMPLEN 16

static void _hexdump(const char *buff, size_t len) 
{
    if(len<=8192)
    {
        unsigned int x = 0, pos = 0, count = 1;
        unsigned int line = 0;

        printf("\n%08x  ", line);
        while(pos<len)
        {
            printf("%02x ",buff[pos++] &0xff);
            if( count==DUMPLEN/2)
            {
                putchar('\x20');
            }else if( count==DUMPLEN)
            {
                unsigned int log;

                printf("|");

                if(pos>=DUMPLEN)
                    log=pos-DUMPLEN;
                else
                    log=pos;

                for(;log<pos;log++)
                    (isalnum( buff[log])||isgraph( buff[log]))?printf("%c",buff[log]):printf(".");

                puts("|");
                printf("%08x  ",line+=DUMPLEN);

                if(pos>(len-DUMPLEN))
                    x = pos;
                count = 0;
            }
            count++;
        }
        if(len!=x)
        {
            for(;(pos-x)<DUMPLEN;pos++)
                printf("\x20\x20\x20");
            printf("|");
            for(;x<len;x++)
                (isalnum( buff[x])||isgraph( buff[x]))?printf("%c",buff[x]):printf(".");
            puts("|");
        }
        printf("%08x\n",line+=--count);
    }
}

void __attribute__((unused))ssniff_hexdump(int socksize, int ethsize, char *buff)
{
    const char *data = (const char *)(buff + 40 + ethsize);
    _hexdump(data,socksize-40-ethsize);
}

