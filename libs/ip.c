/*
 * ipShort.c
 *
*/
#include "proto.h"

extern void ssniff_log(loglevel_e, struct buffer_hdr *);

void *ipShort()
{

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

    for(;;)
    {
        struct buffer_hdr bufhdr = {0};
        if((socksize = recvfrom(sock,buff,sizeof(buff),0,(struct sockaddr *)&sin,&len)) == -1){
            fprintf(stderr,"%d:ipSniff():%s\n",__LINE__,strerror(errno));
            exit(EXIT_FAILURE);
        }


        if(socksize > 0)
        {
            bufhdr.iph = (struct iphdr *)(buff + sizeof(struct ethhdr));

            if (udata->protocol && udata->protocol != bufhdr.iph->protocol)
                continue;

            switch(bufhdr.iph->protocol)
            {
                case IPPROTO_TCP:
                    break;
                case IPPROTO_UDP:
                    bufhdr.udph = (struct udphdr *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
                    break;
                case IPPROTO_ICMP:
                    bufhdr.icmph = (struct icmphdr *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
                    break;
                case IPPROTO_IGMP:
                    bufhdr.igmph = (struct igmp *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
                    break;
                default:
                    continue;
            }

            bufhdr.tcph = (struct tcphdr *)(buff + sizeof(struct iphdr) + sizeof(struct ethhdr));
            ssniff_log(0, &bufhdr);
        }
    }
}

