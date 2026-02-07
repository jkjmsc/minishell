/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:33:10 by jkarippa          #+#    #+#             */
/*   Updated: 2025/08/29 17:36:57 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Problems 1 : Error in test 2: get_next_line(5: "only_nl.txt"):
**				expected: <NULL>,got: ""
** Solution 1 : Check for '\0' once the string is joined. If found free the
**				string and return NULL.
*/
/*
** Problem 2 :	Error in test 3: get_next_line(5: "read_error.txt"):
**				expected: <NULL>, got: "cccccccc"
** 				Probable reason: You should clear the static buffer
** 				when a call to read returns -1
** Solution 2 : When the read() generates -1. It means file read error
** 				To solve that we need an extra flag where we pass it to
** 				join_buffer_with_string() where we free the cache memory
** 				copied to the string and set it to null.
*/
/*
** Problem 3 :	Error that memory is still reachable when countless number
** 				of newlines are provided as *.txt file.
** Solution 3 :	The error pertained is thatthe memory was not freed
** 				and initialized to NULL leading to wrong results.
*/
/*
** Problem 4 :	When the BUFFER_SIZE > the length of the characters to be read
** 				the paco --strict fails stating an error.
** Solution 4 :	Read the files using the BUFFER_SIZE, reallocate the cup_buffer
** 				to the actually required byte_size.
*/
/*
** Problem 5 :	When Valgrind is run you get still reachable memory error.
** Solution 5 :	This is true. But it is not an error, if the no.of block
** 				reachable is 1. This is since, it the "fd" reaches EOF
** 				my fucntion get_next_line() has a cache memory which is
** 				why i have still reachable memory.
*/
#include "get_next_line.h"

/*
** Function to read the file fd and throw error when encountered
** and make the string 'NULL' or else return the read string (can
** also be '\0').
*/
static char	*read_from_file(int fd, int *error, char **string)
{
	int		bytes_read;
	char	*cup_buffer;
	char	*temp;

	cup_buffer = ft_callocg(BUFFER_SIZE + 1, sizeof(char));
	if (cup_buffer == NULL)
		return (free(*string), *string = NULL, NULL);
	bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		*error = 1;
		return (free(*string), *string = NULL, free(cup_buffer), NULL);
	}
	if (bytes_read == 0)
	{
		free(cup_buffer);
		return (NULL);
	}
	if (bytes_read < BUFFER_SIZE)
	{
		temp = ft_substrg(cup_buffer, 0, bytes_read);
		free(cup_buffer);
		cup_buffer = temp;
	}
	return (cup_buffer);
}

/*
** Function to join buffer with string
*/
static char	*join_buffer_with_string(int fd, char *string)
{
	char	*buffer;
	char	*temp;
	int		error;

	error = 0;
	if (!string)
		string = read_from_file(fd, &error, &string);
	while (string && ft_strchrg(string, '\n') == 0 && error != 1)
	{
		buffer = read_from_file(fd, &error, &string);
		if (!buffer)
			break ;
		temp = string;
		string = NULL;
		if (!temp)
			return (free(buffer), NULL);
		string = ft_strjoing(temp, buffer);
		free(temp);
		temp = NULL;
		free(buffer);
		buffer = NULL;
		if (!string)
			return (NULL);
	}
	return (string);
}

/*
** Function to separate cache from the string (cstart = blen)
*/
static char	*separate_cache_from_string(char *string, char **cache)
{
	char	*nline;
	char	*buffer;
	size_t	clen;
	size_t	blen;

	nline = ft_strchrg(string, '\n');
	clen = ft_strleng(string) - (ft_strleng(string) - ft_strleng(nline) + 1);
	blen = ft_strleng(string) - ft_strleng(nline) + 1;
	*cache = ft_substrg(string, blen, clen);
	buffer = ft_substrg(string, 0, blen);
	if ((**cache) == '\0')
	{
		free(*cache);
		(*cache) = NULL;
	}
	return (buffer);
}

/*
** The get_next_line function to get the next line from the fd
*/
char	*get_next_line(int fd)
{
	static char	*cache = NULL;
	char		*string;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (cache != NULL)
	{
		string = cache;
		cache = NULL;
	}
	else
		string = NULL;
	string = join_buffer_with_string(fd, string);
	if (!string || *string == '\0')
		return (free(string), NULL);
	if (ft_strchrg(string, '\n'))
	{
		buffer = string;
		string = NULL;
		string = separate_cache_from_string(buffer, &cache);
		free(buffer);
	}
	return (string);
}

// /*
// ** Function to debug using the ascii code
// */
// static void	print_ascii_debug(const char *label, const char *str, int count)
// {
// 	unsigned char	c;
// 	int				i;

// 	i = 0;
// 	printf("%s[%d]:", label, count);
// 	if (!str)
// 	{
// 		printf("(null)\n");
// 		return ;
// 	}
// 	while (str[i])
// 	{
// 		c = (unsigned char)str[i++];
// 		if (c == '\n')
// 			printf("\\n");
// 		else if (c == '\t')
// 			printf("\\t");
// 		else if (c == '\r')
// 			printf("\\r");
// 		else if (c == ' ')
// 			printf("[space]");
// 		else if (c == '\0')
// 			printf("\\0");
// 		else if (c < 32 || c > 126)
// 			printf("\\x%02x", c);
// 		else
// 			printf("%c", c);
// 	}
// 	printf("\n");
// }

// int	main(void)
// {
// 	int		fd;
// 	char	*next_line;
// 	int		count;
// 	char	file1[20] = "only_nl.txt";
// 	char	file2[20] = "multiple_nl.txt";
// 	char	file3[20] = "variable_nls.txt";
// 	char	file4[20] = "lines_around_10.txt";
// 	char	file5[20] = "read_error.txt";
// 	char	file6[20] = "giant_line.txt";
// 	char	file7[20] = "giant_line_nl.txt";

// 	count = 0;
// 	fd = open(file1, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error opening file");
// 		return (1);
// 	}
// 	// 1
// 	next_line = get_next_line(fd);
// 	print_ascii_debug("\nstring\n", next_line, count++);
// 	free(next_line);
// 	next_line = NULL;
// 	// 2
// 	next_line = get_next_line(fd);
// 	print_ascii_debug("\nstring\n", next_line, count++);
// 	free(next_line);
// 	next_line = NULL;
// 	// 3
// 	next_line = get_next_line(fd);
// 	print_ascii_debug("\nstring\n", next_line, count++);
// 	free(next_line);
// 	next_line = NULL;
// 	// 4
// 	next_line = get_next_line(fd);
// 	print_ascii_debug("\nstring\n", next_line, count++);
// 	free(next_line);
// 	next_line = NULL;
// 	// 5
// 	next_line = get_next_line(fd);
// 	print_ascii_debug("\nstring\n", next_line, count++);
// 	free(next_line);
// 	next_line = NULL;
// 	// 6
// 	next_line = get_next_line(fd);
// 	print_ascii_debug("\nstring\n", next_line, count++);
// 	free(next_line);
// 	next_line = NULL;
// }
