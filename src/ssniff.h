#pragma once
/*
 * ssniff.h
 */

struct buffer_hdr;
void *ssniff_start(int);
void ssniff_hexdump(int, int, char *, const char *);
void ssniff_payload(char *buff, int len);
void ssniff_log(ssize_t len, struct buffer_hdr *);

enum {
    FILTER_TCP = 1,
    FILTER_UDP = 2,
    FILTER_ICMP = 4,
    FILTER_IGMP = 8,
    FILTER_ARP = 16
};

