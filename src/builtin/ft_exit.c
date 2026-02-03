/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:00:00 by jkarippa        #+#    #+#             */
/*   Updated: 2025/12/12 12:00:00 by jkarippa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../errors/errors.h"
#include "../tokenization/token.h"
#include "builtin.h"

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i] || s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** Check if the first token is "exit" command (CMD type).
** If yes, print exit message and return 1 (signal to exit shell).
** Otherwise return 0 (continue normal processing).
*/
int	ft_exit(int argc, char **argv)
{
	int	exit_code;
	int	i;

	i = 1;
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	if (argc == 1)
		return (0);
	if (argc == 2)
	{
		if (!is_numeric(argv[1]))
			return (builtin_error(NUMERIC_ARGUMENT, "exit", argv[1]), 2);
	}
	if (argc > 2)
	{
		while (argv[i])
		{
			if (!is_numeric(argv[i]))
				return (builtin_error(NUMERIC_ARGUMENT, "exit", argv[i]), 2);
			else
				return (builtin_error(TOO_MANY_ARG, "exit", NULL), 1);
			i++;
		}
	}
	return (exit_code = ft_atoi(argv[1]), exit_code % 256);
}
