/*
 * main.h
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

#include "./misc/str.h"


void programUsage(char *name);
void *ipReg();
void *ipShort();
void *ipVerb();
void *dataDump();
void *macSniff();
void *quitNow();
void verifyData(unsigned int c, void *t);
void ipHexdump(const char *ptr, size_t len);
void stripInput(char **s);
void showHex(int socksize, int ethsize, char *buff, const char *data);
void bye();

#define CTRL_C_HANDLER     signal(SIGINT,(void*)bye);

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

typedef struct ip_list
{
    char            **ips;
    unsigned int    len;
}iplist_t;

typedef struct mac_list
{
    char            **macs;
    unsigned int    len;
}maclist_t;

typedef struct port_list
{
    char		**ports;
    unsigned int	len;
}portlist_t;

struct user_data
{
    iplist_t            ipsrc_l;
    iplist_t            ipdst_l;
    maclist_t           macsrc_l;
    maclist_t           macdst_l;
    portlist_t          sport_l;
    portlist_t          dport_l;
    unsigned int        protocol;
    unsigned int        srcport;
    unsigned int        dstport;
    unsigned short int  arp;
    unsigned int        vhex;
};struct user_data  user_data_t;


