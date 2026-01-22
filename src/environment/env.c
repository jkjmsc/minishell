/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 20:22:53 by radandri          #+#    #+#             */
/*   Updated: 2026/01/05 19:30:11 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include "env.h"

static char	*get_value(const char *s)
{
	char	*eq;

	eq = ft_strchr(s, '=');
	if (!eq)
		return (ft_strdup(""));
	return (ft_strdup(eq + 1));
}

static char	*get_key(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (ft_substr(s, 0, i));
}

/*
** This function creates and initializes a t_env structure from the
** environment variables array passed as parameter.
**
** @param envp: Array of strings containing environment variables in the
**               format "KEY=VALUE", typically from main's envp parameter.
**
** @return: Pointer to the newly created t_env structure, or NULL if
**          allocation fails.
**
** Example:
**   char *envp[] = {"PATH=/usr/bin", "HOME=/home/user", NULL};
**   t_env *env = env_init(envp);
**   if (env == NULL)
**       handle_error();
*/
t_env	*env_init(char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;
	char	*key;
	char	*value;

	env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		if (!key || !value)
			return (free(key), free(value), NULL);
		if (safe_malloc((void **)&new, sizeof(t_env)))
			return (free(key), free(value), NULL);
		new->key = key;
		new->value = value;
		new->next = env;
		env = new;
		i++;
	}
	return (env);
}

char	*env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

// char	*env_get_original(const char *key)
// {
// 	return (getenv(key));
// }

int	env_update_shlvl(t_env **env)
{
	const char	*shlvl;
	int			level;
	char		*new_value;

	if (!env)
		return (-1);
	shlvl = env_get(*env, "SHLVL");
	if (!shlvl || !is_number(shlvl))
		level = 1;
	else
	{
		level = ft_atoi(shlvl) + 1;
		if (level < 1)
			level = 1;
	}
	new_value = ft_itoa(level);
	if (!new_value)
		return (-1);
	if (env_set(env, "SHLVL", new_value) != 0)
		return (free(new_value), -1);
	free(new_value);
	return (0);
}
