/*
 * stringInput.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEPCHAR ":"

#define PROTO   "proto"
#define SRC     "src"
#define DST	    "dst"
#define SPORT   "sport"
#define DPORT   "dport"
#define IFACE   "iface"

//local
char *stripCut(char *block);
void setIp(char *ip, int sd);
void setPort(char *ip, int sd);
void Iface(const char *iface, int what);

//extern
void setProto(char *proto);

typedef struct GeneralRules
{
    unsigned int    limit;
    char            *desc;
    char            *rule;
}GeneralRules_t;

GeneralRules_t	GRules[]=
{
    {0,"protocol","proto"},
    {1,"destination ip","dst"},
    {2,"source ip","src"},
    {3,"destination port","dport"},
    {4,"source port","sport"},
    {5,"interface","iface"},
    {-1,NULL,NULL}
};
