/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:05:33 by jkarippa          #+#    #+#             */
/*   Updated: 2025/11/05 21:47:12 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function adds a new line to the end of the file.
void	ft_putendl_fd(char *s, int fd)
{
	int		byteswritten;
	char	c;

	c = '\n';
	byteswritten = write(fd, s, ft_strlen(s));
	byteswritten = write(fd, &c, 1);
	(void)byteswritten;
}
