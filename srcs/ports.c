#include "../includes/ft_nmap.h"

// check for allowed chars
int	check_ports_char(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 48 && str[i] <= 57) || str[i] == 45 || str[i] == 44)
			i++;
		else
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}