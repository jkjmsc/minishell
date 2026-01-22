/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:45:56 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 16:16:52 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function basically compares the 2 strings provided and returns the ascii
// difference if strings differ for size 'n'.
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*a = (const unsigned char *)s1;
	const unsigned char	*b = (const unsigned char *)s2;
	unsigned long		i;

	i = 0;
	while (i < n)
	{
		if (a[i] == b[i])
			i++;
		else
			return (a[i] - b[i]);
	}
	return (0);
}
