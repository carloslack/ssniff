/*
 * $Id: Simple Sniffer,v 0.1 beta Aug 19 BRT 2002 Carlos Carvalho
 *
 * It is not a bad idea to set in your $HOME/.vimrc:
 *
 * set tabstop=4
 *
*/ 
#include <getopt.h>
#include "main.h"

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
            {"verbose", no_argument, &verbose_flag, 1},
            {"short", no_argument, &verbose_flag, 2},
            {"dump", no_argument, &verbose_flag, 3},
            {NULL,0,0,0}
        };

        c = getopt_long(argc, argv, "", long_options, &option_index);

        if(c == -1)
            break;

        switch(verbose_flag)
        {
            case 0:		programUsage(argv[0]);	
                        break;
            case 1:		who = 1;
                        break;
            case 2:		who = 2;
                        break;
            case 3:		who = 3;
                        break;
            default:	who = 0;
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
            case 0: ipReg();
                    break;
            case 1: ipVerb();
                    break;
            case 2:	ipShort();
                    break;
            case 3:	dataDump();
                    break;
            default:break;
        }
    }	
    return 0;
}    
