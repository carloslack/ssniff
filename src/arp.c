/*
 * arp.c
 *
 * Etherenet protocol filter
 */
#include "proto.h"

extern void ssniff_log(loglevel_e, struct buffer_hdr *);

void *macSniff() {
    struct  sockaddr_in sin;

    socklen_t   socksize;
    socklen_t   sock;

    char    buff[8092] = {0};
    unsigned int    len;

    len = sizeof(sin);

    if((sock = socket(PF_PACKET,SOCK_RAW,htons(ETHERTYPE_ARP))) < 0) 
    {
        fprintf(stderr,"%d:macSniff():%s\n",__LINE__,strerror(errno));
        exit(EXIT_FAILURE);
    }

    for(;;)
    {
        struct buffer_hdr bufhdr = {0};
        if((socksize = recvfrom(sock,buff,sizeof(buff),0,(struct sockaddr *)&sin,&len)) == -1)
        {
            fprintf(stderr,"%d:macSniff():%s\n",__LINE__,strerror(errno));
            exit(EXIT_FAILURE);
        }

        if(socksize > 0)
        {
            /* Ethernet frame header */
            bufhdr.eth = (struct ethhdr *)buff;
            /* ARP packet */
            bufhdr.arp = (struct arphdr *)(buff + sizeof(struct ethhdr));
            ssniff_log(socksize, &bufhdr);
            //printf("---%d\n", socksize-sizeof(struct ethhdr));
            //const char      *data;
            //showHex(socksize, sizeof(struct ethhdr), (char*)&buff, (char*)&data);

        }
    }
    return 0;
}
