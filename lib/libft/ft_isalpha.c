/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:18:26 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 13:46:58 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Checks if the ASCII is a letter.
int	ft_isalpha(int c)
{
	int	value;

	if (c < 91 && c > 64)
		value = 1;
	else if (c < 123 && c > 96)
		value = 1;
	else
		value = 0;
	return (value);
}
