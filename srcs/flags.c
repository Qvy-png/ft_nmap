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

int	get_file_size(char *str)
{
	int 	i;
	int		fd;
	char	buff[2];
	
	i = 0;
	fd = -1;
	fd = open(str, O_RDONLY);
	if (fd == -1)
	return -1;
	while(read(fd, buff, 1) != 0)
		i++;
	close(fd);
	return i;
}

int	hostname_syntax(char *str)
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
		if ((tmp[i] >= 'a' && tmp[i] <= 'z') || (tmp[i] >= '0' && tmp[i] <= '9') || tmp[i] == '.' || tmp[i] == '-' || tmp[i] == '\n' || tmp[i] == '\0')
			i++;
		else
			return (free(tmp), EXIT_FAILURE);
	}
	return (free(tmp), EXIT_SUCCESS);
}

// for --file, as long as it fits in the terminal and that it can be opened.. lol
// can only contain standard domain name characters, numbers or/and '.'
// if any hostname poops pants, tactical exit
int	check_file(char *str, struct nmap_luggage *l)
{
	int		fd;
	int		i;
	int		ret;
	int		size;
	char	buff[2];
	char	*file_content;

	i = 0;
	ret = -1;
	fd = -1;
	if (access(str, F_OK | R_OK ) == EXIT_FAILURE)
		return EXIT_FAILURE;

	size = get_file_size(str);
	if (size == -1)
		return EXIT_FAILURE;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return EXIT_FAILURE;

	file_content = malloc(sizeof(char) * size + 1);
	if (file_content == NULL)
		return EXIT_MALLOCS;

	ret = read(fd, buff, 1);
	while (ret != 0)
	{
		file_content[i] = buff[0];
		ret = read(fd, buff, 1);
		i++;
	}
	file_content[i] = '\0';

	if (hostname_syntax(file_content) == EXIT_FAILURE)
		return (free(file_content), EXIT_FAILURE);

	l->file = ft_strdup(file_content);
	if (l->file == NULL)
		return (free(file_content), EXIT_MALLOCS);
	free(file_content);
	return EXIT_SUCCESS;
}

// just calls for hostname_syntax, function name kept for compatibility
int	check_ip(char *str)
{
	if (hostname_syntax(str) == EXIT_FAILURE)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}


// TODO
// for --ports, needs only numbers, ',' and '-', and must be in range 1-1024 by default. total scanned number cannot exceed 1024 ports
// for a range, handle when the range is upside down (first bigger than second) the way it's written, as in, counting down.
int check_ports(char *str)
{
	if (check_ports_char(str) == EXIT_FAILURE)
		return EXIT_FAILURE;
	// needs to check numbers from range


	// needs to check total number of ports scanned


	return EXIT_SUCCESS;
}

//TODO
// for --scan, needs only uppercase alpha, ',' and must be a valid flag between SYN, NULL, ACK, FIN, XMAS, and UDP
int	check_scan(char *str)
{
	(void)str;

	return EXIT_SUCCESS;
}

int	check_speedup(char *str)
{
	int	i;
	int	num;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return EXIT_FAILURE;
	}
	num = atoi(str);
	if (num < 0 || num > 250)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
