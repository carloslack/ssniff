/*
 * usage.c
 *
 * The usage help function
 */

#include <stdio.h>
#include <stdlib.h>

void programUsage(char *name)
{
    printf("Use: %s [ --help | --dump | --short | --verbose ] [ rule:option ]\n",name);
    printf("iface:interface\t\tLocal interface to set promisc\n");
    printf("proto:arp\t\tArp protocol\n");
    printf("proto:icmp\t\tIcmp protocol\n");
    printf("proto:igmp\t\tIgmp protocol\n");
    printf("proto:tcp\t\tTcp protocol\n");
    printf("proto:udp\t\tUdp protocol\n");
    printf("src:[ip,ip..]\t\tSource IP[s]\n");
    printf("dst:[ip,ip..]\t\tDestination IP[s]\n");
    printf("sport:[port,port..]\tSource port *ignored if proto != TCP || proto != UDP\n");
    printf("dport:[port,port..]\tDestination port *ignored if proto != TCP || proto != UDP\n");
    printf("--help:\t\t\tPrint this help\n");
    printf("--dump:\t\t\tShow very basic packet header information plus hexdump-like data dumping\n");
    printf("--short:\t\tShow basic packet header information\n");
    printf("--verbose:\t\tShow complete packet header information plus hexdump-like data dumping\n");
    exit(EXIT_SUCCESS);
}

