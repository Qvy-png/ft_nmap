#include "../includes/ft_nmap.h"

void print_help( void )
{
	// INTRO
	printf("------------------------------------------------------------\n");
	printf("ft_nmap v0.1 ( https://www.youtube.com/watch?v=dQw4w9WgXcQ )\n");
	printf("------------------------------------------------------------\n\n");

	// USAGE
	printf("Usage:\nft_nmap [--help] [--ports [NUMBER/RANGED]] --ip IP_ADDRESS [--speedup [NUMBER]] [--scan [TYPE]]\n");
	printf(" or\n");
	printf("ft_nmap [--help] [--ports [NUMBER/RANGED]] --file FILE [--speedup [NUMBER]] [--scan [TYPE]]\n\n");

	// USAGE DESCRIPTION

	printf("--help		Print this help screen\n");
	printf("--ports		Ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)\n");
	printf("--ip		IP addresses to scan in dot format\n");
	printf("--file		File name containing IP addresses to scan\n");
	printf("--speedup	Amount of parallel threads to use [1-250]\n");
	printf("--scan		SYN/NULL/FIN/XMAS/ACK/UDP\n");
}