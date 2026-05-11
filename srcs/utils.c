#include "../includes/ft_nmap.h"

void    print_help(void)
{
	// INTRO
	printf("------------------------------------------------------------\n");
	printf("ft_nmap v0.1 ( https://www.youtube.com/watch?v=dQw4w9WgXcQ )\n");
	printf("------------------------------------------------------------\n\n");

	// USAGE
	printf("Usage:\nft_nmap [--help] [--ports [NUMBER/RANGE]] --ip IP_ADDRESS [--speedup [NUMBER]] [--scan [TYPE]]\n");
	printf(" or\n");
	printf("ft_nmap [--help] [--ports [NUMBER/RANGE]] --file FILE [--speedup [NUMBER]] [--scan [TYPE]]\n\n");

	// USAGE DESCRIPTION
	printf("--help		Print this help screen\n");
	printf("--ports		Ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)\n");
	printf("--ip		IP addresses to scan in dot format\n");
	printf("--file		File name containing IP addresses to scan\n");
	printf("--speedup	Amount of parallel threads to use [1-250]\n");
	printf("--scan		SYN/NULL/FIN/XMAS/ACK/UDP\n");
}

int     ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i]-s2[i]);
}

size_t		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

int		ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

char	*ft_strdup(char *src)
{
	int		i = 0;
	char	*res;

	while(src[i])
		i++;
	res = (char*)malloc(sizeof(*res) * i + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while(src[i])
	{
		res[i]=src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}


//SPLIT 

static int	count_words(const char *str, char c)
{
	int i;
	int trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char		**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	if (!s || !(split = malloc((count_words(s, c) + 1) * sizeof(char *))))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}