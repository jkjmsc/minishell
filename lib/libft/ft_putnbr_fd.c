/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:14:51 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 15:03:56 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The possible solution for this function with out malloc and free is
// recurcive function for itoi.
// Should have the sign check before calling the recursive function.
// Don't use else if statement use only if statement.
void	itoa_write(long n, int fd)
{
	char	c;

	if (n < 0)
	{
		c = '-';
		write(fd, &c, 1);
		n = -n;
	}
	if (n / 10 != 0)
		itoa_write(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

// Function writes the number as character to the file fd.
void	ft_putnbr_fd(int n, int fd)
{
	itoa_write((long)n, fd);
}
