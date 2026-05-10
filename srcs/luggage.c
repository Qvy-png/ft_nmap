#include "../includes/ft_nmap.h"

void	luggage_init(struct nmap_luggage *l)
{
	l->IP = NULL;
	l->file = NULL;
	l->flags = NULL;
	l->ports = NULL;
	l->speedup = NULL;
	l->ports_num = NULL;
}

void	free_luggage(struct nmap_luggage *l)
{
	if (l->ports)
		free(l->ports);
	if (l->ports_num)
		free(l->ports_num);
	if (l->IP)
		free(l->IP);
	if (l->file)
		free(l->file);
	if (l->flags)
		free(l->flags);
	if (l->speedup)
		free(l->speedup);
	if (l)
		free(l);
}

int		terminator(struct nmap_luggage *l, int ret)
{
	free_luggage(l);
	return ret;
}
