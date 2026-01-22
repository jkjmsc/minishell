/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:47:48 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 15:23:14 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Create a new duplicate string using memory allocation.
char	*ft_strdup(const char *s1)
{
	unsigned int	i;
	char			*new;

	i = 0;
	while (s1[i])
		i++;
	new = malloc(i + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return ((char *)new);
}
