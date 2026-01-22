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
int	ft_exit(t_token *head, int argc, char **argv)
{
	int	exit_code;

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
	if (head == NULL)
		return (0);
	if (head->type == CMD && ft_strncmp(head->value, "exit", 5) == 0)
	{
		terminate_dll(&head);
		return (1);
	}
	exit_code = ft_atoi(argv[1]);
	exit(exit_code % 256);
}
