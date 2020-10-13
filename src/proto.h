#pragma once

/*
 * ssniff.h
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/igmp.h>
#include <netinet/ip_icmp.h>
#include <linux/if_ether.h>
#include <linux/if.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include <net/if_arp.h>
#include <string.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>

#define DEVICE  "eth0"
enum
{
    MIN_PORT=1,
    MAX_PORT=65535,
    BUFFSIZE=8092,
    IPLENGTH=15,
    PORTLENGTH=5,
    MACLENGTH=17,
    MAXMACS=16,
    MAXIPS=16,
    MAXPORTS=16
};


struct buffer_hdr {
    struct  iphdr   *iph;
    struct  tcphdr  *tcph;
    struct  udphdr  *udph;
    struct  icmphdr *icmph;
    struct  igmp    *igmph;
    /* Ethernet */
    struct ethhdr   *eth;
    struct arphdr   *arp;
};

typedef enum{
    MIN = 1,
    MEDIUM,
    MAX
}loglevel_e;

struct proto_unwrap
{
    //IP
    int source_port;
    int destination_port;
    int protocol;
    const char *protocol_name;
    const char *source;
    const char *destination;
};


