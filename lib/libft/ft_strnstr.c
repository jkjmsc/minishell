/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:14:24 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 16:23:28 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The funciton finds the first occurance of the word needle inside the
// haystack.
char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	unsigned long	i;
	unsigned long	j;

	if (!h && len == 0)
	{
		return (NULL);
	}
	i = 0;
	if (n[i] == 0)
		return ((char *)h);
	while (h[i] && i < len)
	{
		j = 0;
		while (n[j] && h[i + j] && (i + j) < len && h[i + j] == n[j])
			j++;
		if (n[j] == '\0')
			return ((char *)(h + i));
		i++;
	}
	return (0);
}
