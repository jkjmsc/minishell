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

#include "../tokenization/token.h"
#include "builtin.h"
#include <unistd.h>

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+' || s[0] == '-')
		i++;
	if (!s[i])
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
static unsigned char	parse_exit_code(const char *str)
{
	unsigned long long	code;
	int					i;
	int					sign;

	i = 0;
	code = 0;
	sign = 1;
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		code = code * 10 + (str[i++] - '0');
	}
	code = code % 256;
	if (sign == -1)
		return ((256 - code) % 256);
	return (code);
}

int	ft_exit(t_token *head, int argc, char **argv)
{
	unsigned char	exit_code;

	if (isatty(STDIN_FILENO))
		printf("exit\n");
	if (argc == 1)
		exit(0);
	if (argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit(2);
	}
	if (head && head->type == CMD && ft_strncmp(head->value, "exit", 5) == 0)
	{
		terminate_dll(&head);
		exit_code = parse_exit_code(argv[1]);
		exit(exit_code);
	}
	exit_code = parse_exit_code(argv[1]);
	exit(exit_code);
}
