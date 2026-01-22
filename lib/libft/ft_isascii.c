/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:24:07 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 13:48:51 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Checks if the provided value is an ASCII or not?
int	ft_isascii(int c)
{
	int	value;

	if (c >= 0 && c <= 127)
		value = 1;
	else
		value = 0;
	return (value);
}
