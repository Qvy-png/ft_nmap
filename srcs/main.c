#include "../includes/ft_nmap.h"

int	flag_to_arg_matcher(char *flag, char *arg, struct nmap_luggage *l)
{
	int	ret;

	ret = -1;
	if (ft_strcmp(flag, ARG_IP) == 0)
	{  //TODO check if values are filled up in struct
		if (l->file != NULL)
			return EXIT_CHOOSER;
		if (l->IP != NULL)
			return EXIT_DOUBLES;

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
	{ //TODO check if values are filled up in struct
		if (l->IP != NULL)
			return EXIT_CHOOSER;
		if (l->file != NULL)
			return EXIT_DOUBLES;

		ret = check_file(arg, l);
		if (ret == EXIT_FAILURE)
			return EXIT_FAILURE;
		else if (ret == EXIT_MALLOCS)
			return EXIT_MALLOCS;
	}
	else if (ft_strcmp(flag, ARG_SCAN) == 0)
	{ //TODO do that
		if (l->flags != NULL)
			return EXIT_DOUBLES;

		ret = check_scan(arg, l);
		if (ret  == EXIT_FAILURE)
			return EXIT_FAILURE;
		else if (ret == EXIT_MALLOCS)
			return EXIT_MALLOCS;
		//TODO DELETE THIS ONCE IT WORKS, IT CAN'T EXIST YET
		// l->scans
		l->flags = ft_strdup(arg);
		

	}
	else if (ft_strcmp(flag, ARG_PORTS) == 0)
	{
		if (l->ports != NULL)
			return EXIT_DOUBLES;
		// TODO check if both ports and ports_num are filled up. You might not need l->ports in the future though.
		ret = check_ports(arg, l);
		if (ret == EXIT_FAILURE)
			return EXIT_FAILURE;
	}
	else if (ft_strcmp(flag, ARG_SPEEDUP) == 0)
	{
		if (l->speedup != -1)
			return EXIT_DOUBLES;
	
		if (check_speedup(arg) == EXIT_FAILURE)
			return EXIT_FAILURE;

		l->speedup = atoi(arg);
	}
	else
		return EXIT_UNKNOWN;
	return EXIT_SUCCESS;
}

int	default_ports_filler(struct nmap_luggage *l)
{
	printf("`--ports` not found, setting default to 1-1024\n");

	if (check_ports("1-1024", l) == EXIT_FAILURE)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

// TODO
int	default_scans_filler(struct nmap_luggage *l)
{
	check_scan("SYN,NULL,ACK,FIN,XMAS,UDP", l);

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
			if (ft_strcmp(argv[i], "--help") == 0)
				return (print_help(), EXIT_FAILURE);
			if (flag_syntax_checker(argv[i]) == EXIT_SUCCESS)
			{
				if (argv[i+1] != NULL)
				{
					ret_matcher = flag_to_arg_matcher(argv[i], argv[i + 1], l);
					if (ret_matcher == EXIT_SUCCESS)
						i++;
					else
					{
						if (ret_matcher == EXIT_DOUBLES)
							return (printf("You can only use `%s` once, please check your command\n", argv[i]), EXIT_FAILURE);
						else if (ret_matcher == EXIT_CHOOSER)
							return (printf("`--file` or `--ip`, there ain't no wonderland..\n"), EXIT_FAILURE);
						else if (ret_matcher == EXIT_MALLOCS)
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

	//TODO if no port has been input, initialize to ports 1-1024 by default, fill l->ports and l->ports_num, as well as l->scans

	if (l->ports_num == NULL)
		default_ports_filler(l);

	if (l->scans == NULL)
		default_scans_filler(l);

	return EXIT_SUCCESS;
}

void	print_debug_separator(void)
{
	printf("\n/////////////////////////////////////////////////\n\n");
}

void	print_luggage(struct nmap_luggage *l)
{

	print_debug_separator();
	if (l->IP)
		printf("--ip\n\nl->IP value :\n\n%s\n", l->IP);
	else
		printf("--ip\n\nl->file value :\n\n%s\n", l->file);
	print_debug_separator();
	printf("--ports\n\nl->ports value :\n\n%s\n%d\n", l->ports, l->ports_num[0]);
	print_debug_separator();
	printf("--speedup\n\nl->speedup value :\n\n%d\n", l->speedup);
	print_debug_separator();
	printf("--scan\n\nl->flags value :\n\n%s\n", l->scans[0]);
	print_debug_separator();

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
	
	//DONE check if the minimum amount of flags have been gathered to proceed with packet forming
	if (l->file == NULL && l->IP == NULL)
		return terminator(l, EXIT_FAILURE);

	//TODO do a little vizualizer function to go through the struct and display the data
	print_luggage(l);

	// printf("hello world?\n");

	// TODO put this in a function and handle clean exit if failure
	// int raw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	// if (raw_socket < 0) {
	// 	perror("Socket creation failed");
	// 	exit(EXIT_FAILURE);
	// }

	return terminator(l, EXIT_SUCCESS);
}
