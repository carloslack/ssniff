/*
 * ipShort.c
 *
*/
#include "main.h"

void *ipShort()
{
    struct  iphdr       *iph;
    struct  tcphdr      *tcph;
    struct  udphdr      *udph;
    struct  icmphdr     *icmph;
    struct  igmp        *igmph;
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

        if(socksize > 0)
        {
            iph = (struct iphdr *)(buff + sizeof(struct ethhdr));
            tcph = (struct tcphdr *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
            udph = (struct udphdr *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
            icmph = (struct icmphdr *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
            igmph = (struct igmp *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));

            switch(iph->protocol)
            {
                case IPPROTO_TCP:   break;
                case IPPROTO_UDP:   break;
                case IPPROTO_ICMP:  break;
                case IPPROTO_IGMP:  break;
                default:            continue;
            }

            if(udata->protocol)
            {
                if(iph->protocol != udata->protocol)
                    continue;
            }else{
                udata->srcport = 0;
                udata->dstport = 0;
            }

            for(i=0; i < udata->ipsrc_l.len && i < MAXIPS; i++)
            {
                if(udata->ipsrc_l.len > 0)
                {
                    if(strcmp( inet_ntop(AF_INET,&iph->saddr,str,sizeof(str)),udata->ipsrc_l.ips[i]))
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
                    if(!strcmp( inet_ntop(AF_INET,&iph->daddr,str,sizeof(str)),udata->ipdst_l.ips[i]))
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
                        case IPPROTO_TCP:   if(htons(tcph->source) != atoi(udata->sport_l.ports[i]))
                                                continue;
                                            break;
                        case IPPROTO_UDP:   if(htons(udph->source) != atoi(udata->sport_l.ports[i]))
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
                        case IPPROTO_TCP:   if(htons(tcph->dest) != atoi(udata->dport_l.ports[i]))
                                                continue;
                                            break;
                        case IPPROTO_UDP:   if(htons(udph->dest) != atoi(udata->dport_l.ports[i]))
                                                continue;
                                            break;
                        default:            break;
                    }
                    i = MAXPORTS + 1;
                    break;
                }
            } if(i <= MAXPORTS && udata->dport_l.len > 0) continue;

            switch(iph->protocol){
                case IPPROTO_TCP:   printf("\n[ip]: protocol:0x%02x (%d TCP)\n",iph->protocol, (int)iph->protocol);
                                    printf("[ip]: source:%s:%d\n",inet_ntop(AF_INET,&iph->saddr,str,sizeof(str)),htons(tcph->source));
                                    printf("[ip]: destination:%s:%d\n",inet_ntop(AF_INET,&iph->daddr,str,sizeof(str)),htons(tcph->dest));
                                    break;


                case IPPROTO_UDP:   printf("\n[ip]: protocol:0x%02x (%d UDP)\n",iph->protocol, (int)iph->protocol);
                                    printf("[ip]: source:%s:%d\n",inet_ntop(AF_INET,&iph->saddr,str,sizeof(str)),htons(tcph->source));
                                    printf("[ip]: destination:%s:%d\n",inet_ntop(AF_INET,&iph->daddr,str,sizeof(str)),htons(tcph->dest));
                                    break;


                case IPPROTO_ICMP:  printf("\n[ip]: protocol:0x%02x (%d ICMP)\n",iph->protocol, (int)iph->protocol);
                                    printf("[ip]: source:%s:%d\n",inet_ntop(AF_INET,&iph->saddr,str,sizeof(str)),htons(tcph->source));
                                    printf("[ip]: destination:%s:%d\n",inet_ntop(AF_INET,&iph->daddr,str,sizeof(str)),htons(tcph->dest));
                                    break;

                case IPPROTO_IGMP:  printf("\n[ip]: protocol:0x%02x (%d IGMP)\n",iph->protocol, (int)iph->protocol);
                                    printf("[ip]: source:%s:%d\n",inet_ntop(AF_INET,&iph->saddr,str,sizeof(str)),htons(tcph->source));
                                    printf("[ip]: destination:%s:%d\n",inet_ntop(AF_INET,&iph->daddr,str,sizeof(str)),htons(tcph->dest));
                                    break;
                default:            break;
            }
        }
    }
}

