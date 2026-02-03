/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 21:21:35 by radandri          #+#    #+#             */
/*   Updated: 2026/01/29 06:42:36 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../errors/errors.h"
#include "builtin.h"

/*
 ** Check if a string is a valid environment variable identifier.
 ** Rules:
 ** - Must start with a letter (a-z, A-Z) or underscore (_).
 ** - Subsequent characters can be letters, digits (0-9), or underscores.
 ** - Can optionally contain an '=' or '+=' to separate key and value.
 */
static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
		{
			if (str[i] == '+' && str[i + 1] == '=')
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	process_export_arg(const char *arg, char *cmd, t_env **env)
{
	char	*equal_sign;

	if (arg[0] == '-')
		return (builtin_error(NOT_A_VALID_IDENTIFIER, cmd, (char *)arg), 2);
	if (!is_valid_identifier(arg))
		return (builtin_error(NOT_A_VALID_IDENTIFIER, cmd, (char *)arg), 1);
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		if (equal_sign > arg && equal_sign[-1] == '+')
			handle_export_append(arg, equal_sign, env);
		else
			handle_export_assign(arg, equal_sign, env);
	}
	return (0);
}

int	ft_export(int argc, char **argv, t_minishell *minishell)
{
	int	i;
	int	status;
	int	ret;

	status = 0;
	if (argc == 1)
		return (print_export_env(minishell->env), 0);
	i = 1;
	while (argv[i])
	{
		ret = process_export_arg(argv[i++], argv[0], &minishell->env);
		if (ret != 0)
		{
			if (ret == 2)
				status = 2;
			else if (status != 2)
				status = 1;
		}
	}
	return (status);
}
