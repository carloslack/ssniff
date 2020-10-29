#pragma once
/*
 * ssniff.h
 */

#include <stdbool.h>
struct buffer_hdr;
void *ssniff_start(int);
void ssniff_hexdump(int, int, char *, const char *);
void ssniff_payload(char *buff, int len);
void ssniff_log(ssize_t len, struct buffer_hdr *, bool verbose);

enum {
    FILTER_TCP = 1,
    FILTER_UDP = 2,
    FILTER_ICMP = 4,
    FILTER_IGMP = 8,
    FILTER_ARP = 16,
    FILTER_VERBOSE = 32
};

