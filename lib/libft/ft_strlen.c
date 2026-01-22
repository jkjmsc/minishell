/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:58:47 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 16:27:19 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function counts the number of characters in the provided string.
size_t	ft_strlen(const char *s)
{
	unsigned long	count;

	count = 0;
	while (s[count])
		++count;
	return (count);
}
