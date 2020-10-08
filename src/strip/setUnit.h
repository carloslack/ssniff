/*
 * setUnit.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../main.h"

void setProto(char *proto);
void setIp(char *ip, int sd);
void setPort(char *port, int sd);

enum
{
	ZERO,
	ICMP,
	ARP=	ICMP,
	IGMP=   2,
	TCP=    6,
	UDP=    17
};

typedef struct ProtoRules
{
	unsigned int    limit;
	unsigned int    protodef;
	char            *proto;
}ProtoRules_t;

ProtoRules_t GProto[]=
{
	{0,0,"arp"},
	{1,1,"icmp"},
	{2,2,"igmp"},
	{3,6,"tcp"},
	{4,17,"udp"},
	{-1,-1,NULL}
};

