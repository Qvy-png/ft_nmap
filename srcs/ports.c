#include "../includes/ft_nmap.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

// check if no double ',' or no double '-', or no port higher than 65'535
int	ports_syntax(char *str)
{
	int		i;
	int		j;
	int		num_alone;
	int		begin_range;
	int		end_range;
	char	*tmp;

	i = 0;
	j = 0;
	begin_range = 0;
	end_range = 0;
	num_alone = 0;
	(void)begin_range;
	(void)end_range;
	(void)num_alone;
	tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\0')
			break; //to avoid segfault before str[i + 1] becomes out of range
		if ((str[i] == ','  || str[i] == '-' ) && (str[i + 1] == ',' || str[i + 1] == '-'))
			return EXIT_FAILURE;
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == ',')
		{

			tmp[j] = '\0';
			
			j = -1; 
		}
		tmp[j] = str[i];
		i++;
		j++;
	}
	free(tmp);
	return EXIT_SUCCESS;
}

// check for allowed chars
int	check_ports_char(char *str)
{
	int i;

	i = 0;
	if (str[0] == ',' || str[0] == '-')
		return EXIT_FAILURE;
	while (str[i] != '\0')
	{
		if ((str[i] >= 0 && str[i] <= 9) || str[i] == ',' || str[i] == '-')
			i++;
		else
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}