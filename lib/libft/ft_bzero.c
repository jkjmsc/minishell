/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:17:58 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 16:07:40 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Write zero bytes to the provided pointer
void	ft_bzero(void *str, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)str;
	i = 0;
	while (i < n)
		p[i++] = 0;
}
