/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:52:27 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 16:29:33 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Note: Here the size is either the destination buffer or should be less than
// the destination buffer to avoid any sedmentation errors
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned long	i;
	unsigned long	len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	return (len);
}
