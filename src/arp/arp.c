/*
 * arp.c
 *
 * Etherenet protocol filter
 */
#include "arp.h"

void *macSniff() {
    struct ethhdr   *eth;
    struct arphdr   *arp;
    struct  sockaddr_in sin;

    socklen_t   socksize;
    socklen_t   sock;

    char    buff[BUFFSIZE];
    unsigned int    i;
    unsigned int    len;
    unsigned char   *data;

    len = sizeof(sin);
    data = NULL;
    i = 0;

    if((sock = socket(PF_PACKET,SOCK_RAW,htons(ETHERTYPE_ARP))) < 0) 
    {
        fprintf(stderr,"%d:macSniff():%s\n",__LINE__,strerror(errno));
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        if((socksize = recvfrom(sock,buff,sizeof(buff),0,(struct sockaddr *)&sin,&len)) == -1)
        {
            fprintf(stderr,"%d:macSniff():%s\n",__LINE__,strerror(errno));
            exit(EXIT_FAILURE);
        }

        if(socksize > 0)
        {
            eth = (struct ethhdr *)buff;
            arp = (struct arphdr *)(buff + sizeof(struct ethhdr));

            printf("\n[eth]h_dest: %02X:%02X:%02X:%02X:%02X:%02X\n",
                    eth->h_dest[0],     
                    eth->h_dest[1],     
                    eth->h_dest[2],    
                    eth->h_dest[3],     
                    eth->h_dest[4],     
                    eth->h_dest[5]);   
            printf("[eth]h_source: %02X:%02X:%02X:%02X:%02X:%02X\n",
                    eth->h_source[0],
                    eth->h_source[1],
                    eth->h_source[2],
                    eth->h_source[3],
                    eth->h_source[4],
                    eth->h_source[5]);

            do
            {
                if(arpOpcode[i].type == ntohs(eth->h_proto))
                    printf("[eth]h_proto: 0x%04x %s\n",ntohs(eth->h_proto),arpOpcode[i].desc);
                i++;
            }while(arpOpcode[i].desc != NULL);i=0;

            do
            {
                if(arpOpcode[i].type == ntohs(arp->ar_pro))
                    printf("[eth]h_proto: 0x%04x %s\n",ntohs(arp->ar_pro),arpOpcode[i].desc);
                i++;
            }while(arpOpcode[i].desc != NULL);i=0;

            printf("[arp]ar_hdr: %u\n", ntohs(arp->ar_hrd));
            printf("[arp]ar_hln: %d\n", arp->ar_hln);
            printf("[apr]ar_pln: %d\n", arp->ar_pln);
            printf("[arp]ar_op: %u\n", ntohs(arp->ar_op)); 
        }
    }
    return 0;
}
