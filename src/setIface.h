/*
 * setIface.h
 */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE "eth0"
#define DEVLEN  5

