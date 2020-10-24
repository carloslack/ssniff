#pragma once

/*
 * ssniff.h
 */

#define UDPLEN sizeof(struct udphdr)
#define ICMPLEN sizeof(struct icmphdr)
#define IPLEN sizeof(struct iphdr)
struct buffer_hdr {
    struct  iphdr   *iph;
    struct  tcphdr  *tcph;
    struct  udphdr  *udph;
    struct  icmphdr *icmph;
    struct  igmp    *igmph;
    /* Ethernet */
    struct ethhdr   *eth;
    struct arphdr   *arp;
    /* Payload */
    char   *raw;
};

