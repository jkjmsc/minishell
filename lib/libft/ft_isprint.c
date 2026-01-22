/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:37:08 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 13:51:43 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Checks if the character is printable or not!
int	ft_isprint(int c)
{
	int	value;

	if (c >= 32 && c <= 126)
		value = 1;
	else
		value = 0;
	return (value);
}
