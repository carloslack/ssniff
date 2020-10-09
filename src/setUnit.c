/*
 * setUnit.c
 *
 * User input parsing
 */

#include "setUnit.h"

void setProto(char *proto)
{
    struct  user_data   *udata;
    udata = &user_data_t;

    if(strstr(proto,"arp"))
    {
        udata->protocol = ZERO;
        udata->arp = ARP;
    }

    if(strstr(proto,"icmp"))
        udata->protocol = ICMP;

    if(strstr(proto,"igmp"))
        udata->protocol = IGMP;

    if(strstr(proto,"tcp"))
        udata->protocol = TCP;

    if(strstr(proto,"udp"))
        udata->protocol = UDP;
}

void setIp(char *ip, int sd)
{
    struct  user_data   *udata;
    udata = &user_data_t;

    unsigned int cnt;

    switch(sd)
    {
        case 0:     if( (cnt = strcnt(ip, ',')+1) > MAXIPS)
                    {
                        fprintf(stderr,"Argument too long: Maximum IPs allowed is: %d.\n",MAXIPS);
                        exit(EXIT_FAILURE);
                    }
                    udata->ipsrc_l.ips = strsplt(ip,',');
                    udata->ipsrc_l.len = cnt;
                    verifyData(0, &udata->ipsrc_l);
                    break;
        case 1:     if( (cnt = strcnt(ip, ',')+1) > MAXIPS)
                    {
                        fprintf(stderr,"Argument too long: Maximum IPs allowed is: %d.\n",MAXIPS);
                        exit(EXIT_FAILURE);
                    }
                    udata->ipdst_l.ips = strsplt(ip,',');
                    udata->ipdst_l.len = cnt;
                    verifyData(0, &udata->ipdst_l);
                    break;
        default:    break;
    }
}

void setPort(char *port, int sd)
{
    struct  user_data   *udata;
    udata = &user_data_t;

    unsigned int cnt;

    switch(sd)
    {
        case 0:     if( (cnt = strcnt(port, ',')+1) > MAXPORTS)
                    {
                        fprintf(stderr,"Argument too long: Maximum PORTs allowed is: %d.\n",MAXPORTS);
                        exit(EXIT_FAILURE);
                    }
                    udata->sport_l.ports = strsplt(port,',');
                    udata->sport_l.len = cnt;
                    verifyData(1, &udata->sport_l);
                    break;
        case 1:     if( (cnt = strcnt(port, ',')+1) > MAXPORTS)
                    {
                        fprintf(stderr,"Argument too long: Maximum PORTs allowed is: %d.\n",MAXPORTS);
                        exit(EXIT_FAILURE);
                    }
                    udata->dport_l.ports = strsplt(port,',');
                    udata->dport_l.len = cnt;
                    verifyData(1, &udata->dport_l);
                    break;
        default:    break;
    }
}

