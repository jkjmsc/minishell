/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:40:26 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 16:14:46 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function returns the pointer positioning to the first occurence of the
// search character or else NULL.
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*source = (const unsigned char *)s;
	size_t				i;

	i = 0;
	while (i < n)
	{
		if (*(source + i) == (unsigned char)c)
			return ((void *)(source + i));
		i++;
	}
	return (0);
}
