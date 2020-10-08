/*
 * verifyData.c
 */

#include "../main.h"

void verifyData(unsigned int c, void *t)
{   
    iplist_t        *ips;
    maclist_t       *macs;
    portlist_t      *ports;
    unsigned int    i;

    switch(c){
        case 0: ips = (iplist_t*)t;
                for(i = 0; i < ips->len; i++)
                {
                    if(ips->ips[i] == NULL || strlen(ips->ips[i])>IPLENGTH)
                    {
                        puts("Invalid IP address");
                        abort();
                    } 
                }
                break;
        case 1: ports = (portlist_t*)t;
                for(i = 0; i < ports->len; i++)
                {
                    if(ports->ports[i] == NULL || strlen(ports->ports[i])>PORTLENGTH)
                    {
                        puts("Invalid port");
                        abort();
                    }
                }
                break;
        case 2: if(atoi(t)>MAX_PORT || atoi(t)<MIN_PORT)
                {
                    puts("Invalid port");
                    abort();
                }
                break;
        case 3: macs = (maclist_t*)t;
                for(i = 0; i < macs->len; i++) 
                {  
                    if(macs->macs[i] == NULL || strlen(macs->macs[i])>MACLENGTH) 
                    {
                        puts("Invalid MAC address");
                        abort();
                    }
                }
                break;
        default:break;
    }
}

