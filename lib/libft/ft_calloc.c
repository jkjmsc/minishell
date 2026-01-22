/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:59:05 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 16:08:52 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// To allocate memory of size and allocate it with zero bytes.
void	*ft_calloc(size_t count, size_t size)
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
