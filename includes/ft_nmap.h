#ifndef FT_TRACEROUTE
# define FT_TRACEROUTE

// base libraries
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>

// thread libraries
# include <pthread.h>

// packet transmission libraries
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>


// EXITS
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

// STRUCTURES
struct iphdr {
    unsigned char ihl : 4;			// Header length (5 = 20 bytes)
    unsigned char version : 4;		// Version (4 for IPv4)
    unsigned char tos;				// Type of service (usually 0)
    unsigned short tot_len;			// Total length (IP header + payload)
    unsigned short id;				// Packet ID (set to a random value)
    unsigned short frag_off;		// Fragment offset (usually 0)
    unsigned char ttl;				// Time to live (e.g., 64)
    unsigned char protocol;			// TCP = 6
    unsigned short check;			// IP checksum (calculated later)
    struct in_addr saddr;			// Source IP (your IP)
    struct in_addr daddr;			// Destination IP (target IP)
};



#endif
