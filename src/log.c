#include <stdbool.h>
#include "proto.h"

typedef struct arpOpcodes{
    int type;
    const char *desc;
}arpOpcodes_t;

static arpOpcodes_t arpOpcode[]=
{
    {0x0800, "IP"},
    {0x0806, "Address Resolution"},
    {0x8035, "Reverse Arp"},
    {0x0200, "Xerox PUP"},
    {0x0060, "Ethernet loopback"},
    {0x0201, "Xeror PUP Addr"},
    {0x22F0, "TSN"},
    {0x0800, "Internet Protocol"},
    {0x0805, "CCITT"},
    {0x08FF, "G8BPQ AX.25"},
    {0x0a00, "Xerox IEEE802.3 PUP"},
    {0x0a01, "Xerox IEEE802.3 PUP"},
    {0x4305, "B.A.T.M.A.N.-Advanced"},
    {0x6000, "DEC Assigned"},
    {0x6001, "DEC DNA Dump/Load"},
    {0x6002, "DEC DNA Remote"},
    {0x6003, "DEC DNA Routing"},
    {0x6004, "DEC LAT"},
    {0x6005, "DEC Diagnostics"},
    {0x6006, "DEC Customer use"},
    {0x6558, "Trans Ether Bridging"},
    {0x8035, "Reverse Addr Res"},
    {0x86DD, "IPv6 over bluebook"},
    {0x8808, "IEEE Pause frames"},
    {-1, ""}
};

static arpOpcodes_t arp_hw_identifiers[]=
{
    {ARPHRD_NETROM, "NET/ROM"},
    {ARPHRD_ETHER, "Ethernet"},
    {ARPHRD_EETHER, "Experimental Ethernet"},
    {ARPHRD_AX25, "AX.25 Level 2"},
    {ARPHRD_PRONET, "PROnet"},
    {ARPHRD_CHAOS, "Chaosnet"},
    {ARPHRD_IEEE802, "IEEE 802.2 Ethernet"},
    {ARPHRD_ARCNET, "ARCnet"},
    {ARPHRD_APPLETLK, "APPLEtalk"},
    {ARPHRD_DLCI, "Frame Relay DLCI"},
    {ARPHRD_ATM, "ATM"},
    {ARPHRD_METRICOM, "Metricom STRIP"},
    {ARPHRD_IEEE1394, "IEEE 1394 IPv4"},
    {ARPHRD_EUI64, "EUI-64"},
    {ARPHRD_INFINIBAND, "InfiniBand"},
    {-1, ""}
};

static arpOpcodes_t arp_protocol_opcodes[]=
{
    {ARPOP_REQUEST, "ARP request"},
    {ARPOP_REPLY,   "ARP reply"},
    {ARPOP_RREQUEST,"RARP request"},
    {ARPOP_RREPLY,   "RARP reply"},
    {ARPOP_InREQUEST, "InARP request"},
    {ARPOP_InREPLY, "InARP reply"},
    {ARPOP_NAK, "ARP NAK"},
    {-1, ""}
};


static const char *translate_arp_id(int id) {
    for (int i = 0; arpOpcode[i].type != -1; ++i) {
        if (id == arpOpcode[i].type)
            return arpOpcode[i].desc;
    }
    return "Unhandled";
}
static const char *translate_arp_op(int id) {
    for (int i = 0; arp_protocol_opcodes[i].type != -1; ++i) {
        if (id == arp_protocol_opcodes[i].type)
            return arp_protocol_opcodes[i].desc;
    }
    return "Unhandled";
}
static const char *translate_hw_type(int id) {
    for (int i = 0; arp_hw_identifiers[i].type != -1; ++i) {
        if (id == arp_hw_identifiers[i].type)
            return arp_hw_identifiers[i].desc;
    }
    return "Unhandled";
}
static const char *translate_arp_protocol(int id) {
    if (id == ETH_P_IP)
        return "IPv4";
    return "Unhandled";
}

static const char *translate_arp_ethernet(int id) {
    if (id == ETH_P_IP)
        return "IPv4";
    return "Unhandled";
}

static bool _ssniff_unwrap_iph(const struct buffer_hdr *hdr, struct proto_unwrap *ret)
{
    if (!hdr || !ret) {
        fprintf(stderr, "Internal error: can't unwrap packet\n");
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
void ssniff_log(socklen_t len, struct buffer_hdr *hdr)
{
    struct proto_unwrap unwrap = {0};

    if (hdr->tcph) {
        int ok = _ssniff_unwrap_iph(hdr, &unwrap);
        if (ok) {
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
    // Ethernet
    } else if (hdr->eth) {
        unsigned char src[ETH_ALEN] = {0};
        unsigned char dst[ETH_ALEN] = {0};
        memcpy(src, hdr->eth->h_source, ETH_ALEN);
        memcpy(dst, hdr->eth->h_dest, ETH_ALEN);
        fprintf(stdout, "%s, %s (len %d), %s (len %d), %s, source %02X:%02X:%02X:%02X:%02X:%02X, destination %02X:%02X:%02X:%02X:%02X:%02X, length %d\n",
                translate_arp_id(ntohs(hdr->eth->h_proto)), translate_hw_type(ntohs(hdr->arp->ar_hrd)),hdr->arp->ar_hln,
                translate_arp_protocol(ntohs(hdr->arp->ar_pro)), hdr->arp->ar_pln, translate_arp_op(ntohs(hdr->arp->ar_op)), 
                src[0], src[1], src[2], src[3], src[4], src[5], dst[0], dst[1], dst[2], dst[3], dst[4], dst[5], len-ETH_HLEN);
    }
}

