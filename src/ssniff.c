/*
 * $Id: Simple Sniffer,v 0.1 beta Aug 19 BRT 2002 Carlos Carvalho
 *
 * It is not a bad idea to set in your $HOME/.vimrc:
 *
 * set tabstop=4
 *
*/ 
#include <getopt.h>
#include "ssniff.h"
#include "proto.h"

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
    exit(EXIT_SUCCESS);
}


int main(int argc, char **argv)
{
    struct  user_data   *udata;
    udata = &user_data_t;

    int c;
    int option_index = 0;
    unsigned int who = 0;
    static int verbose_flag;

    while(1)
    {
        static struct option long_options[]=
        {
            {"help", no_argument, &verbose_flag, 0},
            {"dump", no_argument, &verbose_flag, 2},
            {NULL,0,0,0}
        };

        c = getopt_long(argc, argv, "", long_options, &option_index);

        if(c == -1)
            break;

        switch(verbose_flag)
        {
            case 0:     programUsage(argv[0]);
                        break;
            case 1:     who = 1;
                        break;
            default:    who = 0;
                        break;
        }
    }

    CTRL_C_HANDLER

        stripInput(argv);

    if(udata->arp)
    {
        macSniff();
    }else{
        switch(who)
        {
            case 0: ipShort();
                    break;
            case 1: dataDump();
                    break;
            default:break;
        }
    }
    return 0;
}
