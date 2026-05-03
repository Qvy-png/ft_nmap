#include "../includes/ft_nmap.h"

int	check_ports(char *nums)
{
	int i;

	i = 0;
	while (nums[i] != '\0')
	{
		if ((nums[i] >= 48 && nums[i] <= 57) || nums[i] == 45 || nums[i] == 44)
			i++;
		else
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

