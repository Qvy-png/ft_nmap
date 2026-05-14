#ifndef FT_TRACEROUTE
# define FT_TRACEROUTE

// base libraries
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// thread libraries
# include <pthread.h>

// packet transmission libraries
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>


// EXITS
# define EXIT_CHOOSER 5
# define EXIT_DOUBLES 4
# define EXIT_MALLOCS 3
# define EXIT_UNKNOWN 2
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

// TCP FLAGS
# define SYN	0x02
//		 NULL	0x00
# define ACK	0x10
# define FIN	0x01
# define XMAS	0x29

// ARG FLAGS
# define ARG_IP			"--ip"
# define ARG_FILE		"--file"
# define ARG_SCAN		"--scan"
# define ARG_PORTS		"--ports"
# define ARG_SPEEDUP	"--speedup"


// STRUCTURES
struct	iphdr {

	unsigned	char	ihl : 4;		// Header length (5 = 20 bytes)
	unsigned	char	version : 4;	// Version (4 for IPv4)
	unsigned	char	tos;			// Type of service (usually 0)
	unsigned	short	tot_len;		// Total length (IP header + payload)
	unsigned	short	id;				// Packet ID (set to a random value)
	unsigned	short	frag_off;		// Fragment offset (usually 0)
	unsigned	char	ttl;			// Time to live (e.g., 64)
	unsigned	char	protocol;		// TCP = 6
	unsigned	short	check;			// IP checksum (calculated later)
	struct		in_addr	saddr;			// Source IP (your IP)
	struct		in_addr	daddr;			// Destination IP (target IP)
};

struct	tcphdr {

	unsigned	short	source;			// Source port (random high port)
	unsigned	short	dest;			// Destination port (e.g., 80, 443)
	unsigned	int		seq;			// Sequence number (random)
	unsigned	int		ack_seq;		// Acknowledgment number (0 for SYN)
	unsigned	char	doff : 4;		// Data offset (5 = 20 bytes)
	unsigned	char	res1 : 4;		// Reserved (0)
	unsigned	short	flags;			// TCP flags (SYN = 0x02)
	unsigned	short	window;			// Window size (e.g., 5840)
	unsigned	short	check;			// TCP checksum (calculated later)
	unsigned	short	urg_ptr;		// Urgent pointer (0)
};

struct	nmap_luggage {

	char				*ports;			// Contains the ports range
	int				 	*ports_num;	 	// int values of ports, unsorted
	int					ports_count;	// number of ports

	char				*IP;			// Target IP
	char				*file;			// File content
	char				**file_content;	// File content as a 2D array

	int					speedup;		// Number of threads

	char				*flags;			// String with FLAGS
	char				**scans;		// 2D array with the scan types
};

// typedef struct {
//     struct nmap_luggage **tasks;
//     int count;
//     int size;
//     int front;
//     int rear;
//     pthread_mutex_t mutex;
//     pthread_cond_t cond;
// } ThreadPool;

// FUNCTIONS //

// UTILS
void	print_help(void);
int		ft_tolower(int c);
char	*ft_strdup(char *src);
size_t	ft_strlen(const char *str);
int	 	ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);

// LUGGAGE (helper structure for nmap)
void	free_luggage(struct nmap_luggage *l);
void	luggage_init(struct nmap_luggage *l);
int		terminator(struct nmap_luggage *l, int ret);

// PORTS
int		check_ports_char(char *str);
int		count_numbers(char *input, struct nmap_luggage *l);


// FLAGS
int		check_ip(char *str);

int	 	get_file_size(char *str);
int	 	file_content_check(char *str);
int		flag_syntax_checker(char *str);

int		check_speedup(char *str);
int		check_file(char *str, struct nmap_luggage *l);
int		check_scan(char *str, struct nmap_luggage *l);
int		check_ports(char *str, struct nmap_luggage *l);

// THREADS

int		thread_creator(struct nmap_luggage *l);


#endif
