## About

    Ssnif

    Just another very basic packet dump tool

    Raw sockets ETHERNET/ARP/IP/TCP/ICMP/IGMP sniffer

## Compile
    make

## Run
    (must be ROOT)
    # ./ssniff --help

## Some output ...

### UDP
    192.168.0.16 > 192.168.0.16 UDP (17)
        ihl 5, version 4, tos 0x00, len 78, id 29066, frag off 0, chksum 0x47a8 ttl 128
        IP source E4:AA:EA:D6:87:F5, destination 87:F5:00:00:51:19
        source port 137, dest port 137, len 58, chksum 0x559c
        0000:   E9 15 00 10 00 01 00 00   00 00 00 00 20 43 4B 41    ............ CKA
        0010:   41 41 41 41 41 41 41 41   41 41 41 41 41 41 41 41    AAAAAAAAAAAAAAAA
        0020:   41 41 41 41 41 41 41 41   41 41 41 41 41 00 00 21    AAAAAAAAAAAAA..!
        0030:   00 01                                                ..

### ICMP
    127.0.0.1 > 127.0.0.1 ICMP (1)
        ihl 5, version 4, tos 0x00, len 88, id 47735, frag off 0, chksum 0xc22b ttl 64
        IP source 00:00:00:00:00:00, destination 00:00:00:00:00:00
        type 0, code 0, chksum 00537, id 29835 sequence 1
        0000:   48 61 74 69 6E 67 20 70   6F 70 75 6C 61 72 20 74    Hating popular t
        0010:   68 69 6E 67 73 20 64 6F   65 73 6E 27 74 20 6D 61    hings doesn't ma
        0020:   6B 65 20 79 6F 75 20 61   6E 20 69 6E 74 65 72 65    ke you an intere
        0030:   73 74 69 6E 67 20 70 65   72 73 6F 6E                sting person

### IGMP
    224.0.0.22 > 224.0.0.22 IGMP (2)
        ihl 6, version 4, tos 0xc0, len 48, id 0, frag off 64, chksum 0x433d ttl 1
        IP source 78:0C:B8:7C:51:19, destination 51:19:00:00:00:16
        type 148, code 4, chksum 0x0000 group 34.0.9.7
        0000:   00 00 00 02 02 00 00 00   E0 00 00 FB 02 00 00 00    ................
        0010:   EF FF FF FA                                          ....

## TODO
    - Select interface to listen
    - Add filters: IP's, ports, etc...
