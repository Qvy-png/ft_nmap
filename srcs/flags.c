# include "../includes/ft_nmap.h"

// checks basic flag syntax (lowercase alpha + '-')
int	flag_syntax_checker(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 97 && str[i] <= 122) || str[i] == '-')
			i++;
		else
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

//TODO
// for --file, needs to be a viable linux file (please search online for that)
int	check_file(char *str)
{
	(void)str;
	return EXIT_SUCCESS;
}

// for --ip, needs only lowercase alpha, '.', '-', and must be between 2 and 
int	check_ip(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		
		i++;
	}
	return EXIT_SUCCESS;
}

// TODO
// for --ports, needs only numbers, ',' and '-', and must be in range 1-1024. total scanned number cannot exceed 1024 ports
int check_ports(char *str)
{
	if (check_ports_char(str) == EXIT_FAILURE)
		return EXIT_FAILURE;
	// needs to check numbers from range

	// needs to check total number of ports scanned(?)

	return EXIT_SUCCESS;
}

//TODO
// for --scan, needs only uppercase alpha, ',' and must be a valid flag between SYN, NULL, ACK, FIN, XMAS, and UDP
int	check_scan(char *str)
{
	(void)str;

	return EXIT_SUCCESS;
}

//TODO
// for --speedup needs only numbers, and must be in range 0-250
int	check_speedup(char *str)
{
	(void)str;

	return EXIT_SUCCESS;
}