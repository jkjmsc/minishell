/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:21:35 by radandri          #+#    #+#             */
/*   Updated: 2026/01/29 21:21:35 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

/*
 ** Sort the environment variables char** alphabetically by key.
 */
void	sort_env_tab(char **env)
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

static void	print_export_line(char *line)
{
	int	j;

	j = 0;
	printf("declare -x ");
	while (line[j] && line[j] != '=')
		printf("%c", line[j++]);
	if (line[j] == '=')
	{
		printf("=\"");
		while (line[++j])
			printf("%c", line[j]);
		printf("\"");
	}
	printf("\n");
}

void	print_export_env(t_env *env)
{
	char	**tab;
	int		i;

	tab = env_to_array(env);
	sort_env_tab(tab);
	i = 0;
	while (tab[i])
	{
		print_export_line(tab[i]);
		free(tab[i++]);
	}
	free(tab);
}

void	handle_export_append(const char *arg, char *equal_sign, t_env **env)
{
	char	*key;
	char	*value;
	char	*appended;
	char	*existing_value;

	key = ft_substr(arg, 0, equal_sign - arg - 1);
	value = ft_strdup(equal_sign + 1);
	existing_value = env_get(*env, key);
	if (existing_value)
	{
		appended = ft_strjoin(existing_value, value);
		env_set(env, key, appended);
		free(appended);
	}
	else
		env_set(env, key, value);
	free(key);
	free(value);
}

void	handle_export_assign(const char *arg, char *equal_sign, t_env **env)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	env_set(env, key, value);
	free(key);
	free(value);
}
