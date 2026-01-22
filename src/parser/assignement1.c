/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:23:35 by codespace         #+#    #+#             */
/*   Updated: 2026/01/21 18:32:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment/env.h"
#include "../utils/utils.h"
#include "../tokenization/token.h"

int	process_assignment(t_env **env, const char *token)
{
	char	*key;
	char	*value;
	char	*expanded;

	if (!is_assignment(token))
		return (0);
	if (split_key_value_assignment(token, &key, &value) != 0)
		return (-1);
	expanded = expand_value(value, *env);
	free(value);
	if (!expanded)
	{
		free(key);
		return (-1);
	}
	if (env_set(env, key, expanded) != 0)
	{
		free(key);
		free(expanded);
		return (-1);
	}
	free(key);
	free(expanded);
	return (1);
}

void	process_all_assignments(t_token *head, t_env **env)
{
	t_token	*current;

	current = head;
	while (current)
	{
		process_assignment(env, current->value);
		current = current->next;
	}
}
