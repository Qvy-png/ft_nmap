#include "../includes/ft_nmap.h"

// Allowed flags : --ip OR --file, --ports, --speedup, --scan, --help 
// If flag --help found, print_help() and exit


// TODO add nmap_luggage in arguments to gather the flag values
int	flag_to_arg_matcher(char *flag, char *arg)
{
	if (ft_strcmp(flag, ARG_IP) == 0)
	{
		// TODO needs to check for length of hostname/domain-name/valid IP
		// length would be [2-63] chars, before .smth, example : hi.com, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.com
		// valid IP would be 4 sets of numbers in range 1-255, separated by '.'
		if (check_ip(arg) == EXIT_FAILURE)
			return EXIT_FAILURE;
	}
	else if (ft_strcmp(flag, ARG_FILE) == 0)
	{
		if (check_file(arg) == EXIT_FAILURE)
			return EXIT_FAILURE;
	}
	else if (ft_strcmp(flag, ARG_SCAN) == 0)
	{
		if (check_scan(arg) == EXIT_FAILURE)
			return EXIT_FAILURE;
	}
	else if (ft_strcmp(flag, ARG_PORTS) == 0)
	{
		if (check_ports(arg) == EXIT_FAILURE)
			return EXIT_FAILURE;
	}
	else if (ft_strcmp(flag, ARG_SPEEDUP) == 0)
	{
		if (check_speedup(arg) == EXIT_FAILURE)
			return EXIT_FAILURE;
	}
	else
	{
		printf("WOMP WOMP\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

// requirements for flags handling :
//	can only be ports, ip or file, scan, speedup

int	handle_args(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-') //most be followed by valid related argument
		{
			if (flag_syntax_checker(argv[i]) == EXIT_SUCCESS)
			{
				if (flag_to_arg_matcher(argv[i], argv[i + 1]) == EXIT_SUCCESS)
					i++;
				else
				{
					printf("The flag `%s` doesn't match with the argument `%s`... \nSomething's wrong with your syntax, I can feel it...\n", argv[i], argv[i + 1]);
					return EXIT_FAILURE;
				}
			}
		}
		else
		{
			printf("You can't be there on your own, little argument!\n");
			return EXIT_FAILURE;
		}
		i++;
	}
	return EXIT_FAILURE;
}

// for IP file, the file MUST contain a single value per line,
// and can only contain standard domain name characters, numbers or/and '.'



int main(int argc, char **argv)
{
	int arg_ret;
	// struct nmap_luggage	*l;

	if (argc <= 1)
	{
		print_help();
		return EXIT_SUCCESS;
	}
	arg_ret = handle_args(argv);
	if (arg_ret == EXIT_FAILURE)
		return EXIT_FAILURE;

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
