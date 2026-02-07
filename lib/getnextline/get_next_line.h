/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:33:17 by jkarippa          #+#    #+#             */
/*   Updated: 2025/08/29 17:36:54 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
// # include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*
** Defining the number of characters read at a time
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

char	*get_next_line(int fd);
void	*ft_callocg(size_t count, size_t size);
char	*ft_strjoing(char const *s1, char const *s2);
size_t	ft_strleng(const char *s);
char	*ft_strchrg(const char *source, int c);
char	*ft_substrg(char const *s, unsigned int start, size_t len);
#endif
