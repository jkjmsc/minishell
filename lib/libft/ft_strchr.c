/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:35:28 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 15:20:28 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function returns a new pointer for the string source when it finds
// the first character c.
char	*ft_strchr(const char *source, int c)
{
	unsigned int	i;
	char			*s;

	i = 0;
	s = (char *)source;
	while (s[i])
	{
		if (*(s + i) == (char)c)
			return (s + i);
		i++;
	}
	if ((char)c == '\0')
		return (s + i);
	else
		return (0);
}
