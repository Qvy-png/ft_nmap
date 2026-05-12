#include "../includes/ft_nmap.h"

// check if no double ',' or no double '-', or no port higher than 65'535
// int	ports_syntax(char *str)
// {
// 	int		i;
// 	int		j;
// 	int		num_alone;
// 	int		begin_range;
// 	int		end_range;
// 	char	*tmp;

// 	i = 0;
// 	j = 0;
// 	begin_range = 0;
// 	end_range = 0;
// 	num_alone = 0;
// 	(void)begin_range;
// 	(void)end_range;
// 	(void)num_alone;
// 	tmp = malloc(sizeof(char) * ft_strlen(str) + 1);
// 	while (str[i])
// 	{
// 		if (str[i] == '\0')
// 			break; //to avoid segfault before str[i + 1] becomes out of range
// 		if ((str[i] == ','  || str[i] == '-' ) && (str[i + 1] == ',' || str[i + 1] == '-'))
// 			return EXIT_FAILURE;
// 		i++;
// 	}
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '-' || str[i] == ',')
// 		{

// 			tmp[j] = '\0';
			
// 			j = -1; 
// 		}
// 		tmp[j] = str[i];
// 		i++;
// 		j++;
// 	}
// 	free(tmp);
// 	return EXIT_SUCCESS;
// }

// check for allowed chars
// int		check_ports_char(char *str)
// {
// 	// int i;

// 	// i = 0;
// 	// // if (str[0] == ',' || str[0] == '-')
// 	// // 	return EXIT_FAILURE;
// 	// while (str[i] != '\0')
// 	// {
// 	// 	if ((str[i] < '0' || str[i] > '9') && str[i] != ',' && str[i] != '-')
// 	// 		return EXIT_FAILURE;
// 	// 	else
// 	// 		i++;
// 	// }
// 	(void)str;
// 	return EXIT_SUCCESS;
// }

int		already_exists(int nums[], int size, int value)
{
    int i;
	
	i = 0;
    while (i < size)
    {
        if (nums[i] == value)
            return EXIT_FAILURE;
        i++;
    }
    return EXIT_SUCCESS;
}

int		add_number(int **numbers, int *size, int *capacity, int value)
{
    int *new_array;

    if (already_exists(*numbers, *size, value) == EXIT_FAILURE)
        return (printf("`--ports` error: duplicate number detected (%d)\n", value), EXIT_FAILURE);

    // Resize array if full
    if (*size >= *capacity)
    {
        *capacity *= 2;

        new_array = realloc(*numbers, sizeof(int) * (*capacity));
        if (new_array == NULL)
        {
            printf("`--ports` error: memory allocation failed\n");
            return EXIT_MALLOCS;
        }
        *numbers = new_array;
    }

    (*numbers)[*size] = value;
    (*size)++;

    return EXIT_SUCCESS;
}

int		is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int		str_to_int(char *str, int start, int end)
{
	int i;
    int result;

	i = start;
	result = 0;
    while (i <= end)
        result = result * 10 + (str[i++] - '0');

    return result;
}

int		process_token(char *token, int start, int end, int **numbers, int *size, int *capacity)
{
	int i;
	int	ret;
	int left;
	int right;
    int dash_pos;


	i = start;
	dash_pos = -1;
    while (i <= end)
    {
        if (token[i] == '-')
        {
            if (dash_pos != -1)
				return (printf("`--ports` error: multiple '-' in range\n"), EXIT_FAILURE);
            dash_pos = i;
        }
        else if (!is_digit(token[i]))
			return (printf("`--ports` error: invalid character '%c'\n", token[i]), EXIT_FAILURE);
        i++;
    }

    if (dash_pos == -1)
    {
        int value = str_to_int(token, start, end);

		if (value == 0)
			return (printf("`--ports` error: 0 is not allowed\n"), EXIT_FAILURE);
		if (value > 65535)
			return (printf("`--ports error: exceeding max port value\n"), EXIT_FAILURE);

		ret = add_number(numbers, size, capacity, value);
        if (ret != EXIT_SUCCESS)
            return ret;
        // if (ret == EXIT_FAILURE)
        //     return EXIT_FAILURE;
		// else if (ret == EXIT_MALLOCS)
		// 	return EXIT_MALLOCS;

        return EXIT_SUCCESS;
    }

    if (dash_pos == start || dash_pos == end)
		return (printf("`--ports` error: invalid range format\n"), EXIT_FAILURE);

    right = str_to_int(token, dash_pos + 1, end);
    left = str_to_int(token, start, dash_pos - 1);
	if (right > 65535 || left > 65535)
			return (printf("`--ports error: exceeding max port value\n"), EXIT_FAILURE);

	if (left == 0 || right == 0)
		return (printf("`--ports` error: ranges cannot contain 0\n"), EXIT_FAILURE);

    if (left > right)
		return (printf("`--ports` error: backward range (%d-%d)\n", left, right), EXIT_FAILURE);

    i = left;

    while (i <= right)
    {
		ret = add_number(numbers, size, capacity, i);
        if (ret != EXIT_SUCCESS)
            return ret;
        // if (ret == EXIT_FAILURE)
        //     return EXIT_FAILURE;
		// else if (ret == EXIT_MALLOCS)
		// 	return EXIT_MALLOCS;
        i++;
    }

	return EXIT_SUCCESS;
}

int		parse_string(char *str, int **numbers)
{
    int i;
	int	ret;
    int size;
    int start;
    int capacity;


	i = 0;
	size = 0;
	start = 0;
	capacity = 10; //random default value
    *numbers = malloc(sizeof(int) * capacity);
    if (*numbers == NULL)
        return (printf("`--ports` error: malloc failed\n"), -2); //because EXIT_FAILURE returns a positive value but it may interpret it wrong since EXIT_MALLOCS == 3

    while (42069) //lol
    {
        if (str[i] == ',' || str[i] == '\0')
        {
            if (i == start)
                return (printf("`--ports` error: empty token\n"), -1);

			ret = process_token(str, start, i - 1, numbers, &size, &capacity);
            if (ret == EXIT_FAILURE)
                // return (free(*numbers), -1);
                return (-1);
			else if (ret == EXIT_MALLOCS)
				// return (free(*numbers), -2);
				return (-2);
	
            start = i + 1;
        }
        if (str[i] == '\0')
            break;
        i++;
    }
    return size;
}

/* MAIN FUNCTION TO CALL */
int	count_numbers(char *input, struct nmap_luggage *l)
{
    int count;
    // int *numbers;

    count = parse_string(input, &l->ports_num);
	if (count == -2)
		return -2;
    else if (count == -1)
        return -1;
	else if (count > 1024)
		return (printf("`--ports` error: number of ports needs to be between 1 and 1024 included\n"), -1);
    // printf("\nTotal count: %d\n", count);

    // free(l->ports_num);
	return count;
}
