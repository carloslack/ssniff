/*
 * $Id: Simple Sniffer,v 0.1 beta Aug 19 BRT 2002 Carlos Carvalho
 *
 * It is not a bad idea to set in your $HOME/.vimrc:
 *
 * SSniff uses raw sockets - root required!
 *
 * set tabstop=4
 *
*/ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proto.h"
#include "ssniff.h"

static void help(char *name)
{
    fprintf(stdout, "Usage: %s <all | arp tcp udp icmp igmp> [--verbose]\n",name);
    fprintf(stdout, " all: filter all available protocols\n");
    fprintf(stdout, " arp, tcp, udp, icmp, igmp: filter correspondent protocol(s)\n");
    fprintf(stdout, "E.g.: \n ./ssniff tcp udp icmp --verbose\n");
    exit(EXIT_SUCCESS);
}


int main(int argc, char **argv)
{
    int flags = 0;

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "--verbose"))
            flags |= FILTER_VERBOSE;
        if (!strncasecmp(argv[i], "all", 3))
        {
            flags |= FILTER_TCP | FILTER_UDP |
                FILTER_ICMP | FILTER_IGMP | FILTER_ARP;
        } else {
            if (!strncasecmp(argv[i], "tcp", 3))
                flags |= FILTER_TCP;
            if (!strncasecmp(argv[i], "udp", 3))
                flags |= FILTER_UDP;
            if (!strncasecmp(argv[i], "icmp", 4))
                flags |= FILTER_ICMP;
            if (!strncasecmp(argv[i], "igmp", 4))
                flags |= FILTER_IGMP;
            if (!strncasecmp(argv[i], "arp", 3))
                flags |= FILTER_ARP;
        }
    }

    if (!flags)
        help(argv[0]);

    // never return
    ssniff_start(flags);

    return 0;
}
