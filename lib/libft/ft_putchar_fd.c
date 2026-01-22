/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:45:17 by jkarippa          #+#    #+#             */
/*   Updated: 2025/11/05 21:45:56 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function writes the input parameter character to the file address fd.
void	ft_putchar_fd(char c, int fd)
{
	int	byteswritten;

	byteswritten = write(fd, &c, 1);
	(void)byteswritten;
}
