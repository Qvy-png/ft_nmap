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

	l->file_content = ft_split(file_content, '\n');
	if (l->file_content == NULL)
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


// for --ports, needs only numbers, ',' and '-', and must be in range 1-1024 by default. total scanned number cannot exceed 1024 ports
// for a range, don't handle when the range is upside down (first bigger than second).
// 0 (zero) is also not a valid value, and a port cannot exceed 65535.
int check_ports(char *str, struct nmap_luggage *l)
{
	int	ret;

	ret = count_numbers(str, l);
	if (ret == -2)
		return EXIT_MALLOCS;
	else if (ret == -1)
		return EXIT_FAILURE;

	l->ports = ft_strdup(str);
	if (l->ports == NULL)
		return EXIT_MALLOCS;
	l->ports_count = ret;

	return EXIT_SUCCESS;
}


int	check_scan_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'A' && str[i] <= 'Z') || str[i] == ',')
			i++;
		else
			return (printf("`--scan error: '%c' is not a valid char\n", str[i]), EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}

int	check_scan_value(char **tab)
{
	int	i;

	i = 0;
	while(tab[i] != NULL)
	{
		if (ft_strcmp(tab[i], "SYN") != EXIT_SUCCESS && \
			ft_strcmp(tab[i], "NULL") != EXIT_SUCCESS && \
			ft_strcmp(tab[i], "ACK") != EXIT_SUCCESS && \
			ft_strcmp(tab[i], "FIN") != EXIT_SUCCESS && \
			ft_strcmp(tab[i], "XMAS") != EXIT_SUCCESS && \
			ft_strcmp(tab[i], "UDP") != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}
		i++;
	}
	return EXIT_SUCCESS;
}

// for --scan, needs only uppercase alpha, ',' and must be a valid flag between SYN, NULL, ACK, FIN, XMAS, and UDP
int	check_scan(char *str, struct nmap_luggage *l)
{
	if (check_scan_chars(str) == EXIT_FAILURE)
		return EXIT_FAILURE;

	// split for the different scans
	l->scans = ft_split(str, ',');
	if (l->scans == NULL)
		return EXIT_MALLOCS;
	if (check_scan_value(l->scans) == EXIT_FAILURE)
		return EXIT_FAILURE;
	l->flags = ft_strdup(str);
	if (l->flags == NULL)
		return EXIT_MALLOCS;
	return EXIT_SUCCESS;
}

int	check_speedup(char *str)
{
	int	i;
	int	num;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return EXIT_FAILURE;
		i++;
	}
	num = atoi(str);
	if (num < 0 || num > 250)
		return (printf("`--speedup` error: argument needs to be in interval [0-250]\n"), EXIT_FAILURE);

	return EXIT_SUCCESS;
}


