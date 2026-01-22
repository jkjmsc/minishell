/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 02:02:49 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 16:24:19 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copies a substring from the source string of size len
// To get rid of the malloc error altered the function to have
// different memory allocation.
// Resolved the problem where if start = null is sent it allocates 1 byte
// and saves '\0'.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*new;
	unsigned int	s_len;
	unsigned int	allo;

	i = 0;
	s_len = ft_strlen((char *)s);
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
