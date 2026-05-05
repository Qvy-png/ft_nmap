#include "../includes/ft_nmap.h"

// Allowed flags : --ip OR --file, --ports, --speedup, --scan, --help 
// If flag --help found, print_help() and exit


// TODO add nmap_luggage in arguments to gather the flag values
// requirements for flags handling :
//	can only be ports, ip or file, scan, speedup
int	flag_to_arg_matcher(char *flag, char *arg, struct nmap_luggage *l)
{
	int	ret;

	ret = -1;
	if (ft_strcmp(flag, ARG_IP) == 0)
	{
		if (check_ip(arg) == EXIT_FAILURE)
			return EXIT_FAILURE;
		else
		{
			l->IP = ft_strdup(arg);
			if (l->IP == NULL)
				return EXIT_MALLOCS;
		}
	}
	else if (ft_strcmp(flag, ARG_FILE) == 0)
	{
		ret = check_file(arg, l);
		if (ret == EXIT_FAILURE)
			return EXIT_FAILURE;
		else if (ret == EXIT_MALLOCS)
			return EXIT_MALLOCS;
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
		return EXIT_UNKNOWN;
	return EXIT_SUCCESS;
}

int	handle_args(char **argv, struct nmap_luggage *l)
{
	int i;
	int	ret_matcher;

	i = 1;
	ret_matcher = -1;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			if (flag_syntax_checker(argv[i]) == EXIT_SUCCESS)
			{
				if (argv[i+1] != NULL)
				{
					ret_matcher = flag_to_arg_matcher(argv[i], argv[i + 1], l);
					if (ret_matcher == EXIT_SUCCESS)
						i++;
					else
					{
						if (ret_matcher == EXIT_MALLOCS)
							return EXIT_MALLOCS;
						else if (ret_matcher == EXIT_FAILURE)
							printf("The flag `%s` doesn't match with the argument `%s`... \nSomething's wrong with your syntax, I can feel it...\n", argv[i], argv[i + 1]);
						else
							printf("Mate, that flag `%s` doens't exist, please have a look at the --help flag.. \n", argv[i]);
						return EXIT_FAILURE;
					}
				}
				else
					printf("The flag `%s` doesn't have an argument... Like, for real? What did you expect?\n", argv[i]);
			}
		}
		else
		{
			printf("You can't be there on your own, little argument!\n");
			return EXIT_FAILURE;
		}
		i++;
	}
	return EXIT_SUCCESS;
}


int main(int argc, char **argv)
{
	int					ret_arg;
	struct nmap_luggage	*l;

	if (argc <= 1)
	{
		print_help();
		return EXIT_SUCCESS;
	}

	l = malloc(sizeof(struct nmap_luggage) + 1);
	if (l == NULL)
		return EXIT_MALLOCS;
	luggage_init(l);

	ret_arg = handle_args(argv, l);
	if (ret_arg == EXIT_FAILURE)
		return terminator(l, EXIT_FAILURE);
	else if (ret_arg == EXIT_MALLOCS)
		return (printf("Stopping here, memory allocation has failed somewhere..\n"), terminator(l, EXIT_MALLOCS));


	// TODO put this in a function and handle clean exit if failure
	// int raw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	// if (raw_socket < 0) {
	// 	perror("Socket creation failed");
	// 	exit(EXIT_FAILURE);
	// }

	return terminator(l, EXIT_SUCCESS);
}
