/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 01:56:55 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 16:19:24 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Sets the n blocks from the start of the adress of the pointer to
// provided character.
void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*p;
	unsigned long	i;

	p = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		p[i++] = (unsigned char)c;
	}
	return (str);
}
