/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:14:59 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 13:45:20 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Checks if the ASCII is a number or a letter.
int	ft_isalnum(int c)
{
	int	value;

	if (c < 91 && c > 64)
		value = 1;
	else if (c < 123 && c > 96)
		value = 1;
	else if (c > 47 && c < 58)
		value = 1;
	else
		value = 0;
	return (value);
}
