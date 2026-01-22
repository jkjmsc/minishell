/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 21:21:35 by radandri          #+#    #+#             */
/*   Updated: 2026/01/16 06:42:36 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../errors/errors.h"
#include "builtin.h"

/*
 ** Check if a string is a valid environment variable identifier.
 ** Rules:
 ** - Must start with a letter (a-z, A-Z) or underscore (_).
 ** - Subsequent characters can be letters, digits (0-9), or underscores.
 ** - Can optionally contain an '=' character to separate key and value.
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
			return (0);
		i++;
	}
	return (1);
}

/*
 ** Sort the environment variables char** alphabetically by key.
 */
static void	sort_env_tab(char **env)
{
	int		i;
	int		swapped;
	char	*tmp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (env[i] && env[i + 1])
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

static void	print_export_env(t_env *env)
{
	char	**tab;
	int		i;

	tab = env_to_array(env);
	sort_env_tab(tab);
	i = 0;
	while (tab[i])
	{
		printf("declare -x %s\n", tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	process_export_arg(const char *arg, char *cmd, t_env **env)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	if (!is_valid_identifier(arg))
		return (builtin_error(NOT_A_VALID_IDENTIFIER, cmd, (char *)arg));
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
		env_set(env, key, value);
		free(key);
		free(value);
	}
}

int	ft_export(int argc, char **argv, t_env **env)
{
	int	i;

	if (argc == 1)
		return (print_export_env(*env), 0);
	i = 1;
	while (argv[i])
		process_export_arg(argv[i++], argv[0], env);
	return (0);
}
