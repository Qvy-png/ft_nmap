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
// Sounds like it could be anything, as long as it fits in the terminal and that it can be opened.. lol
// the file MUST contain a single value per line,
// and can only contain standard domain name characters, numbers or/and '.'

// so for the todo, gotta open file, check each line for valid hostnames.
// if any hostname poops pants, tactical exit

int	check_file(char *str)
{
	(void)str;
	return EXIT_SUCCESS;
}

// TODO needs to check for length of hostname/domain-name/valid IP
// length would be [2-63] chars, before .smth, example : hi.com, aaa-aaaaaaaaaaaaaaaaaaa-aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.com
// so it would be alphanumerical, all handled as lowercase (even if uppercase is being written), with '.' and '-' allowed.
// valid IP would be 4 sets of numbers in range 1-255, separated by '.'
int	check_ip(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strdup(str);
	while (tmp[++i])
		tmp[i] = ft_tolower(tmp[i]);
	i = 0;
	while (tmp[i])
	{
		printf("%c", tmp[i]);
		i++;
	}
	free(tmp);
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
