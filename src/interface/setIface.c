/*
 * setIface.c
 *
 * Set/unset the promisc flag on selected interface
 */

#include "setIface.h"

void setIface(const char *ifC)
{
    if(strlen(ifC)>DEVLEN)
    {
        fprintf(stderr,"%d:setIface():Wrong device name\n",__LINE__);
        exit(EXIT_FAILURE);
    }

    struct  ifreq   ifr;
    socklen_t       sock;
    const char *iiface = ifC;
    iiface = ifC;
    giface = (char*)ifC;
    on = 1;

    if((sock = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL)))<0){
        fprintf(stderr,"%d:setIface():%s\n",__LINE__,strerror(errno));
        exit(EXIT_FAILURE);
    }

    vsnprintf(ifr.ifr_name,strlen(iiface)+1, iiface, NULL);

    if(ioctl(sock,SIOCGIFFLAGS,&ifr) < 0){
        fprintf(stderr,"%d:setIface():%s\n",__LINE__,strerror(errno));
        exit(EXIT_FAILURE);
    }

    ifr.ifr_flags |= IFF_PROMISC; 

    if(ioctl(sock,SIOCSIFFLAGS,&ifr) < 0){
        fprintf(stderr,"%d:setIface():%s\n",__LINE__,strerror(errno));
        exit(EXIT_FAILURE);
    }

    close(sock);

    printf("%s: +promisc\n",iiface);

}

void *quitNow()
{
    struct  ifreq   ifr;
    socklen_t       sock;

    const char *iiface = giface;

    if((sock = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL)))<0){
        fprintf(stderr,"%d:quitNow():socket:%s\n",__LINE__,strerror(errno));
        exit(EXIT_FAILURE);
    }

    vsnprintf(ifr.ifr_name,strlen(iiface)+1, iiface, NULL);

    if(ioctl(sock,SIOCGIFFLAGS,&ifr)<0){
        fprintf(stderr,"%d:quitNow():ioctl:%s\n",__LINE__,strerror(errno));
        exit(EXIT_FAILURE);
    }

    ifr.ifr_flags &= ~IFF_PROMISC;

    if(ioctl(sock,SIOCSIFFLAGS,&ifr)<0){
        fprintf(stderr,"%d:quitNow():ioctl:%s\n",__LINE__,strerror(errno));
        exit(EXIT_FAILURE);
    }
    close(sock);

    printf("%s: -promisc\n",iiface);

    exit(EXIT_SUCCESS);
}

void Iface(char **iface, void *which)
{
    int x = (int)which;

    switch(x)
    {
        case 1:	
            setIface((char*)iface);
            break;

        default:    quitNow();
                    break;
    }
}

void bye()
{
    if(on)
        Iface(NULL,0);
    else
        exit(EXIT_SUCCESS);
}
