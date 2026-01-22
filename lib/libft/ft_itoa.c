/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 01:32:16 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 13:53:46 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// A helper function to help count the number of digits in the integer
static int	count_digits(int n)
{
	int		len;
	long	num;

	len = 0;
	num = n;
	if (num <= 0)
	{
		len++;
		num = -num;
	}
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

// function that creates a string out of the integer provided
char	*ft_itoa(int n)
{
	int		len;
	long	num;
	char	*str;

	len = count_digits(n);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	num = n;
	if (num < 0)
		num = -num;
	if (n == 0)
		str[0] = '0';
	while (num != 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
