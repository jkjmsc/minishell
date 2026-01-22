/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:28:42 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 13:50:26 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Checks if the inputed values is a number or not!
int	ft_isdigit(int c)
{
	int	value;

	if (c > 47 && c < 58)
		value = 1;
	else
		value = 0;
	return (value);
}
