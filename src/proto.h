#pragma once

/*
 * ssniff.h
 */

#define IPLEN sizeof(struct iphdr)
#define UDPLEN sizeof(struct udphdr)
#define ICMPLEN sizeof(struct icmphdr)
#define IGMPLEN sizeof(struct igmp)

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

