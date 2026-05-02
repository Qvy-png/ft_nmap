#include "../includes/ft_nmap.h"


int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	if (argc <= 1)
	{
		print_help();
		return EXIT_SUCCESS;
	}

	int raw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if (raw_socket < 0) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}


	return (0);
}
