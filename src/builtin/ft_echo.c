/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:00:00 by jkarippa          #+#    #+#             */
/*   Updated: 2026/01/11 01:25:28 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenization/token.h"
#include "builtin.h"
#include <stdio.h>

/*
** Helper function to check if a string is a valid -n flag
*/
static int	is_n_flag(char *s)
{
	int	i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	if (s[i] != 'n')
		return (0);
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

/*
** Echo builtin using argv array (null-terminated)
** Supports multiple -n flags
*/
int	ft_echo(char **argv)
{
	int	no_newline;
	int	first;
	int	i;

	no_newline = 0;
	first = 1;
	i = 1;
	while (argv && argv[i] && is_n_flag(argv[i]))
	{
		no_newline = 1;
		i++;
	}
	while (argv && argv[i])
	{
		if (!first)
			printf(" ");
		printf("%s", argv[i]);
		first = 0;
		i++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
