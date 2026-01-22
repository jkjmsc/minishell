/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:03:43 by radandri          #+#    #+#             */
/*   Updated: 2026/01/06 07:36:13 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include "env.h"

int	is_number(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if (s[0] == '+' || s[0] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

t_env	*env_remove(t_env *env, const char *key)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = env;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (env);
		}
		prev = curr;
		curr = curr->next;
	}
	return (env);
}

void	env_count(t_env *env, t_env **curr, int *count)
{
	*count = 0;
	*curr = env;
	while (*curr)
	{
		(*count)++;
		*curr = (*curr)->next;
	}
}

/*
 ** Convert t_env to array of string
 ** Example:
 ** out[0] = GJS_DEBUG_OUTPUT=stderr
 ** out[1] = NVM_CD_FLAGS
 ** out[2] = LOGNAME=radandri
 */
char	**env_to_array(t_env *env)
{
	char	**envp;
	t_env	*curr;
	int		count;
	int		i;
	size_t	key_len;

	env_count(env, &curr, &count);
	safe_malloc((void **)&envp, sizeof(char *) * (count + 1));
	curr = env;
	i = 0;
	while (curr)
	{
		key_len = ft_strlen(curr->key);
		if (safe_malloc((void **)&envp[i], key_len + ft_strlen(curr->value)
				+ 2))
			return (NULL);
		ft_strcpy(envp[i], curr->key);
		envp[i][key_len] = '=';
		ft_strcpy(envp[i] + key_len + 1, curr->value);
		i++;
		curr = curr->next;
	}
	return (envp[i] = NULL, envp);
}
