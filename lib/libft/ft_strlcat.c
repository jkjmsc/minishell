/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:28:12 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 16:28:35 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function basically joins the second string to the first string.
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned long	d;
	unsigned long	s;
	unsigned long	i;

	d = 0;
	s = 0;
	while (d < size && dest[d])
		d++;
	while (src[s])
		s++;
	if (d == size)
		return (size + s);
	i = 0;
	while (src[i] && (d + i + 1) < size)
	{
		dest[d + i] = src[i];
		i++;
	}
	if (d + i < size)
		dest[d + i] = '\0';
	return (d + s);
}
