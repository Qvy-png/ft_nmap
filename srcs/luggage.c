#include "../includes/ft_nmap.h"

void	luggage_init(struct nmap_luggage *l)
{
	l->IP = NULL;
	l->file = NULL;
	l->file_content = NULL;

	l->flags = NULL;
	l->scans = NULL;
	
	l->ports = NULL;
	l->ports_count = 0;
	l->ports_num = NULL;
	
	l->speedup = -1;
}

void	free_luggage(struct nmap_luggage *l)
{
	int	i;

	if (l->ports)
		free(l->ports);
	if (l->ports_num)
		free(l->ports_num);
	if (l->IP)
		free(l->IP);
	if (l->file)
		free(l->file);
	i = 0;
	if (l->file_content)
	{
		while (l->file_content[i] != NULL)
			free(l->file_content[i++]);
		free(l->file_content);
	}
	if (l->flags)
		free(l->flags);
	i = 0;
	if (l->scans)
	{
		while (l->scans[i] != NULL)
			free(l->scans[i++]);
		free(l->scans);
	}
	if (l)
		free(l);
}

int		terminator(struct nmap_luggage *l, int ret)
{
	free_luggage(l);
	return ret;
}
