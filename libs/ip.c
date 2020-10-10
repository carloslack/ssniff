/*
 * ipShort.c
 *
*/
#include "proto.h"

extern void ssniff_log(loglevel_e, struct buffer_hdr *);

void *ipShort()
{
    struct buffer_hdr bufhdr;

    struct  sockaddr_in	sin;
    struct  user_data   *udata;

    socklen_t       sock, socksize;
    unsigned int    len;
    char            buff[BUFFSIZE], str[INET_ADDRSTRLEN];
    const char      *data;
    register long   i;

    len = sizeof(sin);
    data = NULL;
    udata = &user_data_t;

    if((sock = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL))) == -1){
        fprintf(stderr,"%d:ipSniff():%s\n",__LINE__,strerror(errno));
        exit(EXIT_FAILURE);
    }

    memset(buff,'\0',sizeof(buff));

    while(1)
    {
        if((socksize = recvfrom(sock,buff,sizeof(buff),0,(struct sockaddr *)&sin,&len)) == -1){
            fprintf(stderr,"%d:ipSniff():%s\n",__LINE__,strerror(errno));
            exit(EXIT_FAILURE);
        }

        memset(&bufhdr, 0, sizeof(struct buffer_hdr));

        if(socksize > 0)
        {
            bufhdr.iph = (struct iphdr *)(buff + sizeof(struct ethhdr));
            bufhdr.tcph = (struct tcphdr *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
            bufhdr.udph = (struct udphdr *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));

            switch(bufhdr.iph->protocol)
            {
                case IPPROTO_TCP:   break;
                case IPPROTO_UDP:   break;
                case IPPROTO_ICMP:  break;
                case IPPROTO_IGMP:  break;
                default:            continue;
            }

            // TODO: Fix all this mess
            if(udata->protocol)
            {
                if(bufhdr.iph->protocol != udata->protocol)
                    continue;
            }else{
                udata->srcport = 0;
                udata->dstport = 0;
            }

            for(i=0; i < udata->ipsrc_l.len && i < MAXIPS; i++)
            {
                if(udata->ipsrc_l.len > 0)
                {
                    if(strcmp( inet_ntop(AF_INET,&bufhdr.iph->saddr,str,sizeof(str)),udata->ipsrc_l.ips[i]))
                    {
                        i = MAXIPS + 1;
                        break;
                    }
                }
            } if(i <= MAXIPS && udata->ipsrc_l.len > 0) continue;

            for(i=0; i< udata->ipdst_l.len && i < MAXIPS; i++) 
            {
                if(udata->ipdst_l.len > 0)
                {
                    if(!strcmp( inet_ntop(AF_INET,&bufhdr.iph->daddr,str,sizeof(str)),udata->ipdst_l.ips[i]))
                    {
                        i = MAXIPS + 1;
                        break;
                    }
                }

            } if(i <= MAXIPS && udata->ipdst_l.len > 0) continue;

            for(i=0; i< udata->sport_l.len && i < MAXPORTS; i++)
            {
                if(udata->sport_l.len > 0)
                {
                    switch(udata->protocol)
                    {
                        case IPPROTO_TCP:   if(htons(bufhdr.tcph->source) != atoi(udata->sport_l.ports[i]))
                                                continue;
                                            break;
                        case IPPROTO_UDP:   if(htons(bufhdr.udph->source) != atoi(udata->sport_l.ports[i]))
                                                continue;
                                            break;
                        default:            break;
                    }
                    i = MAXPORTS + 1;
                    break;
                }
            } if(i <= MAXPORTS && udata->sport_l.len > 0) continue;

            for(i=0; i< udata->dport_l.len && i < MAXPORTS; i++)
            {
                if(udata->dport_l.len > 0)
                {
                    switch(udata->protocol)
                    {
                        case IPPROTO_TCP:   if(htons(bufhdr.tcph->dest) != atoi(udata->dport_l.ports[i]))
                                                continue;
                                            break;
                        case IPPROTO_UDP:   if(htons(bufhdr.udph->dest) != atoi(udata->dport_l.ports[i]))
                                                continue;
                                            break;
                        default:            break;
                    }
                    i = MAXPORTS + 1;
                    break;
                }
            } if(i <= MAXPORTS && udata->dport_l.len > 0) continue;

            //here
            ssniff_log(0, &bufhdr);
        }
    }
}

