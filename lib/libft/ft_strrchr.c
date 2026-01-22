/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:32:51 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 15:54:46 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function find the last occurrence of a character in a string.
char	*ft_strrchr(const char *source, int c)
{
	unsigned int	i;
	int				flag;
	char			*s;

	i = 0;
	flag = -1;
	s = (char *)source;
	while (s[i])
	{
		if (*(s + i) == (char)c)
			flag = i;
		i++;
	}
	if (flag != -1)
		return (s + flag);
	else
	{
		if ((char)c == '\0')
			return (s + i);
		else
			return (0);
	}
}
