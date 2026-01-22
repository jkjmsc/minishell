/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:52:19 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 15:31:05 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function joins 2 strings together to a new string and writes it to a new
// string.
char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned long	count_s1;
	unsigned long	count_s2;
	unsigned int	i;
	unsigned int	j;
	char			*s3;

	count_s1 = ft_strlen(s1);
	count_s2 = ft_strlen(s2);
	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(count_s1 + count_s2 + 1);
	if (s3 == NULL)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}
