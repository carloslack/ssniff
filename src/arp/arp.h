/*
 * arp.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <ctype.h>
#include <errno.h>
    
#define DEVICE  "eth0"

enum {
    BUFFSIZE=8092,
};

typedef struct arpOpcodes{
    unsigned int    type;
    char            *desc;
}arpOpcodes_t;

arpOpcodes_t arpOpcode[]=
{
    {0x0800,                 "IP"},
    {0x0806, "Address resolution"},
    {0x8035,        "Reverse Arp"},
    {0x0200,          "Xerox PUP"},
    {0x0000,                 NULL}
};

