#include <stdbool.h>
#include "proto.h"

static bool _ssniff_unwrap_pkt(const struct buffer_hdr *hdr, struct proto_unwrap *ret)
{
    if (!hdr || !ret) {
        printf(stderr, "Internal error: can't unwrap packet\n");
        return false;
    }

    char source[INET_ADDRSTRLEN+1] = {0};
    char destination[INET_ADDRSTRLEN+1] = {0};
    const char *src = inet_ntop(AF_INET, &hdr->iph->saddr, source, sizeof(source));
    const char *dst = inet_ntop(AF_INET, &hdr->iph->daddr, destination, sizeof(destination));
    int proto = hdr->iph->protocol;

    // Unwrap IP
    (*ret).source_port = htons(hdr->tcph->source);
    (*ret).destination_port = htons(hdr->tcph->dest);
    (*ret).source = src ? src : "";
    (*ret).destination = dst ? dst : "";

    switch (proto) {
        case IPPROTO_TCP:
            (*ret).protocol_name = "TCP";
            break;
        case IPPROTO_UDP:
            (*ret).protocol_name = "UDP";
            break;
        case IPPROTO_ICMP:
            (*ret).protocol_name = "ICMP";
            break;
        case IPPROTO_IGMP:
            (*ret).protocol_name = "IGMP";
            break;
        default:
            (*ret).protocol_name = "UNKNOWN";
            break;
    }

    return true;
}

void ssniff_log(loglevel_e level, struct buffer_hdr *hdr)
{
    struct proto_unwrap unwrap = {0};
    int ok = _ssniff_unwrap_pkt(hdr, &unwrap);

    if (ok) {
        fprintf(stdout, "%s.%d > %s.%d: %s\n", unwrap.source, unwrap.source_port, unwrap.destination, unwrap.destination_port, unwrap.protocol_name);
    }

}

