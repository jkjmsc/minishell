/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:20:13 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 15:07:44 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function to count words
static unsigned long	count_words(char const *s, char c)
{
	unsigned long	count;
	int				i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

// Count the number of characters in a word for memory allocation
static unsigned long	count_char(char const *s, char c, int pt)
{
	unsigned long	count;

	count = 0;
	while (s[pt])
	{
		if (s[pt] == c)
			break ;
		pt++;
		count++;
	}
	return (count);
}

// Free all words on malloc failure
static void	free_split(char **split, unsigned long i)
{
	while (i--)
		free(split[i]);
	free(split);
}

// Function to check if the allocation is correct or not!
static int	alloc_check(char **split, unsigned long i)
{
	if (!split[i])
	{
		free_split(split, i);
		return (1);
	}
	else
		return (0);
}

// The function splits the provided string to different
// words based on the delimiter provided by the user.
char	**ft_split(char const *s, char c)
{
	char			**split;
	unsigned long	cs;
	unsigned long	cw;
	unsigned long	i;
	int				pos;

	cs = count_words(s, c);
	split = (char **)malloc((cs + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	pos = 0;
	i = 0;
	while (i < cs)
	{
		while (s[pos] == c)
			pos++;
		cw = count_char(s, c, pos);
		split[i] = (char *)malloc(cw + 1);
		if (alloc_check(split, i))
			return (NULL);
		ft_strlcpy(split[i++], &s[pos], cw + 1);
		pos = pos + cw;
	}
	split[i] = NULL;
	return (split);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char s[200] = "      split       this for   me  !       ";
// 	int count = 0;
// 	count = count_words(s, ' ');
// 	printf("Number of words in given string are: %d\n", count);
// 	count = count_char(s, ' ', 5);
// 	printf("Number of letters in given word are: %d\n", count);
// 	char **sp;
// 	sp = ft_split("hello!", ' ');
// 	int i = 0;
// 	while (sp[i] != 0)
// 	{
// 		printf("Word: %s\n", sp[i]);
// 		i++;
// 	}
// 	return (0);
// }