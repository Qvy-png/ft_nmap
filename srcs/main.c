#include "../includes/ft_nmap.h"

// requirements for flags handling :
//	only alpha and '-'
//	can only be ports, ip or file, scan, speedup

int	handle_args(char **argv)
{
	int i;
	// int j;

	i = 1;
	// j = 0;
	while (argv[i])
	{
		if (argv[i][0] == '-')
			printf("flag!\n");
		else
			printf("flagn't!\n");
		i++;
	}

	return EXIT_FAILURE;
}

// for IP file, the file MUST contain a single value per line,
// and can only contain standard domain name characters, numbers or/and '.'



int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	// struct nmap_luggage	*l;

	if (argc <= 1)
	{
		print_help();
		return EXIT_SUCCESS;
	}
	handle_args(argv);

	// l = malloc(sizeof(struct nmap_luggage) + 1);

	printf("%d\n", check_ports("1-2"));
	return EXIT_SUCCESS;

	int raw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if (raw_socket < 0) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}

	return (0);
}
