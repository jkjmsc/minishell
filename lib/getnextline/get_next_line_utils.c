/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:33:02 by jkarippa          #+#    #+#             */
/*   Updated: 2025/08/29 17:25:49 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** The function copies a substring from the source string of size len
*/
char	*ft_substrg(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*new;
	unsigned int	s_len;
	unsigned int	allo;

	i = 0;
	s_len = ft_strleng((char *)s);
	if (start >= s_len)
	{
		new = malloc(1);
		if (!new)
			return (NULL);
		new[0] = '\0';
		return (new);
	}
	allo = len;
	if (s_len - start < len)
		allo = s_len - start;
	new = malloc(allo + 1);
	if (new == NULL)
		return (NULL);
	while (s[start] && i < len)
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}

/*
** The function joins 2 strings together to a new string and writes it to a new
** string.
*/
char	*ft_strjoing(char const *s1, char const *s2)
{
	unsigned long	count_s1;
	unsigned long	count_s2;
	unsigned int	i;
	unsigned int	j;
	char			*s3;

	count_s1 = ft_strleng(s1);
	count_s2 = ft_strleng(s2);
	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(count_s1 + count_s2 + 1);
	if (s3 == NULL)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

/*
** The function returns a new pointer for the string source when it finds
** the first character c.
*/
char	*ft_strchrg(const char *source, int c)
{
	unsigned int	i;
	char			*s;

	i = 0;
	if (source == NULL)
		return (0);
	s = (char *)source;
	while (s[i])
	{
		if (*(s + i) == (char)c)
			return (s + i);
		i++;
	}
	if ((char)c == '\0')
		return (s + i);
	else
		return (0);
}

/*
** The function counts the number of characters in the provided string.
*/
size_t	ft_strleng(const char *s)
{
	unsigned long	count;

	count = 0;
	while (s[count])
		++count;
	return (count);
}

/*
** Function to allocate memory of size and allocate it with zero bytes.
*/
void	*ft_callocg(size_t count, size_t size)
{
	void			*ptr;
	char			*p;
	unsigned long	i;

	i = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	p = (char *)ptr;
	while (i < (count * size))
		p[i++] = 0;
	return ((void *)ptr);
}
