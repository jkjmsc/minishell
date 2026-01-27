/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:45:40 by radandri          #+#    #+#             */
/*   Updated: 2026/01/21 18:38:11 by radandri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include "env.h"

static t_env	*env_find(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static char	*dup_value_or_empty(const char *value)
{
	if (value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static int	env_update_node(t_env *node, const char *value)
{
	char	*dup;

	dup = dup_value_or_empty(value);
	if (!dup)
		return (-1);
	free(node->value);
	node->value = dup;
	return (0);
}

static int	env_prepend(t_env **env, const char *key, const char *value)
{
	t_env	*new;
	char	*kdup;
	char	*vdup;

	if (safe_malloc((void **)&new, sizeof(t_env)))
		return (-1);
	kdup = ft_strdup(key);
	vdup = dup_value_or_empty(value);
	if (!kdup || !vdup)
	{
		free(kdup);
		free(vdup);
		free(new);
		return (-1);
	}
	new->key = kdup;
	new->value = vdup;
	new->next = *env;
	*env = new;
	return (0);
}

int	env_set(t_env **env, const char *key, const char *value)
{
	t_env	*node;

	if (!env || !key || key[0] == '\0')
		return (-1);
	node = env_find(*env, key);
	if (node)
		return (env_update_node(node, value));
	return (env_prepend(env, key, value));
}
