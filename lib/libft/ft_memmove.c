/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:10:03 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 16:18:47 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// It copies from source to destination but avoids overlap without using buffer.
// Reverse copy -> s<d && Foward copy -> s>d
void	*ft_memmove(void *destination, const void *source, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)source;
	unsigned long		i;

	if (destination == NULL && source == NULL)
		return (NULL);
	d = (unsigned char *)destination;
	if (s < d)
	{
		i = n;
		while (i-- > 0)
			d[i] = s[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (destination);
}
