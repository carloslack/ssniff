/*
 * ip.c
 *
*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include "ssniff.h"
#include "proto.h"

#define BUFFSIZE 8092

void *ssniff_start(int flags)
{
    int sock;
    struct sockaddr_in sin;
    unsigned int len = sizeof(sin);
    bool verbose = flags & FILTER_VERBOSE;

    if((sock = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL))) == -1){
        fprintf(stderr,"socket: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for(;;)
    {
        struct buffer_hdr bufhdr = {0};
        char buff[BUFFSIZE] = {0};
        ssize_t socksize;
        if((socksize = recvfrom(sock,buff,sizeof(buff),0,(struct sockaddr *)&sin,&len)) == -1){
            fprintf(stderr,"recvfrom: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        if(socksize > 0)
        {
            bufhdr.eth = (struct ethhdr *)buff;
            if ((flags & FILTER_ARP) && ntohs(bufhdr.eth->h_proto) == ETH_P_ARP)
            {
                bufhdr.arp = (struct arphdr *)(buff + sizeof(struct ethhdr));
                ssniff_log(socksize, &bufhdr);
            } else {
                bufhdr.iph = (struct iphdr *)(buff + sizeof(struct ethhdr));
                if ((flags & FILTER_TCP) && IPPROTO_TCP == bufhdr.iph->protocol)
                {
                    bufhdr.tcph = (struct tcphdr *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
                    ssniff_log(socksize, &bufhdr);
                }
                else if ((flags & FILTER_UDP) && IPPROTO_UDP == bufhdr.iph->protocol)
                {
                    if (verbose)
                        bufhdr.raw = (buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
                    bufhdr.udph = (struct udphdr *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
                    ssniff_log(socksize, &bufhdr);
                }
                else if ((flags & FILTER_ICMP) && IPPROTO_ICMP == bufhdr.iph->protocol)
                {
                    if (verbose)
                        bufhdr.raw = (buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
                    bufhdr.icmph = (struct icmphdr *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
                    ssniff_log(socksize, &bufhdr);
                }
                else if ((flags & FILTER_IGMP) && IPPROTO_IGMP == bufhdr.iph->protocol)
                {
                    if (verbose)
                        bufhdr.raw = (buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
                    bufhdr.igmph = (struct igmp *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
                    ssniff_log(socksize, &bufhdr);
                }
            }
        }
    }
}

