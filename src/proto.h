#pragma once

/*
 * ssniff.h
 */

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

