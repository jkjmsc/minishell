/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:00:11 by jkarippa          #+#    #+#             */
/*   Updated: 2025/11/05 21:46:13 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function inserts a string to the file named fd.
void	ft_putstr_fd(char *s, int fd)
{
	int	byteswritten;

	byteswritten = write(fd, s, ft_strlen(s));
	(void)byteswritten;
}
