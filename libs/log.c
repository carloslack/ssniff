#include <stdbool.h>
#include "proto.h"

static bool _ssniff_unwrap_iph(const struct buffer_hdr *hdr, struct proto_unwrap *ret)
{
    if (!hdr || !ret) {
        printf(stderr, "Internal error: can't unwrap packet\n");
        return false;
    }

    char source[INET_ADDRSTRLEN+1] = {0};
    char destination[INET_ADDRSTRLEN+1] = {0};
    // Unwrap IP
    const char *src = inet_ntop(AF_INET, &hdr->iph->saddr, source, sizeof(source));
    const char *dst = inet_ntop(AF_INET, &hdr->iph->daddr, destination, sizeof(destination));
    int proto = hdr->iph->protocol;

    (*ret).protocol = proto;
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
    int ok = _ssniff_unwrap_iph(hdr, &unwrap);

    if (ok && hdr->tcph) {
        struct  tcphdr  *tcp = hdr->tcph;
        fprintf(stdout, "%s.%d > %s.%d: %s (%d)\n",
                unwrap.source, unwrap.source_port, unwrap.destination, unwrap.destination_port, unwrap.protocol_name, unwrap.protocol);
        fprintf(stdout, "\tihl %u, version %u, tos 0x%02x, len %u, id %u, frag off %u, chksum 0x%04x ttl %d\n",
                hdr->iph->ihl, hdr->iph->version, hdr->iph->tos, htons(hdr->iph->tot_len), htons(hdr->iph->id), hdr->iph->frag_off, hdr->iph->check & 0xFFFF, hdr->iph->ttl);
        //TCP
        fprintf(stdout, "\tseq %d, ack seq %d, res1 %u, doff %u, fin %u, syn %u, rst %u, psh %u, ack %u, urg %u, res2 %u, window %u, chksum 0x%04x, urg ptr %u\n",
                htons(tcp->seq), htons(tcp->ack_seq), tcp->res1, tcp->doff, tcp->fin, tcp->syn, tcp->rst, tcp->psh, tcp->ack, tcp->urg, tcp->res2, htons(tcp->window), tcp->check & 0xFFFF, tcp->urg_ptr);

        // UDP packet
        if (hdr->udph) {
            struct  udphdr  *udp = hdr->udph;
            fprintf(stdout, "\tsource %u, dest %u, len %u, chksum 0x%04x\n",
                    htons(udp->source), htons(udp->dest), htons(udp->len), udp->check & 0xFFFF);
        }

        // ICMP packet
        else if (hdr->icmph) {
            struct  icmphdr  *icmp = hdr->icmph;
            fprintf(stdout, "\ttype %u, code %u, chksum 0%04x, id %u sequence %u\n",
                    icmp->type, icmp->code, icmp->checksum & 0xFFFF, htons(icmp->un.echo.id), htons(icmp->un.echo.sequence));
        }

        // IGMP packet
        else if (hdr->igmph) {
            struct  igmp  *igmp = hdr->igmph;
            fprintf(stdout, "\ttype %u, code %u, chksum 0x%04x\n",
                    igmp->igmp_type, igmp->igmp_code, igmp->igmp_cksum & 0xFFFF);
        }
    }
}

