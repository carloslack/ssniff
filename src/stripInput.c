/*
 * stripInput.c
 *
 * Perform preliminary user input parsing
 */

#include "stripInput.h"

void strCut(char *block)
{
    unsigned int x;

    char *pos_0 = strsep(&block,SEPCHAR);
    char *pos_1 = strsep(&block,SEPCHAR);

    for(x=0;GRules[x].limit!=-1;x++)
    {
        if(!strcmp(pos_0,GRules[x].rule))
        {
            if(!strcmp(pos_0, PROTO))
                setProto(pos_1);

            if(!strcmp(pos_0, SRC))
                setIp(pos_1,0);

            if(!strcmp(pos_0, DST))
                setIp(pos_1,1);

            if(!strcmp(pos_0, SPORT))
                setPort(pos_1,0);

            if(!strcmp(pos_0, DPORT))
                setPort(pos_1,1);

            if(!strcmp(pos_0, IFACE))
                Iface((char *)pos_1,1);
        }
    }
}


void stripInput(char **args)
{
    unsigned int i;

    for(i=1;args[i]!=NULL;i++)
        strCut(args[i]);
}

