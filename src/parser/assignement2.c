/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:00:00 by radandri          #+#    #+#             */
/*   Updated: 2026/01/22 00:00:00 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment/env.h"
#include "../../lib/libft/libft.h"

static int	has_plus_operator(const char *token)
{
	int	i;

	i = 0;
	while (token[i] && token[i] != '=')
		i++;
	if (i > 0 && token[i - 1] == '+')
		return (1);
	return (0);
}

int	process_compound_assignment(t_env **env, const char *token, char *key,
		char *expanded)
{
	char	*current_val;
	char	*result;

	if (!has_plus_operator(token))
		return (env_set(env, key, expanded));
	current_val = env_get(*env, key);
	if (!current_val)
		current_val = "";
	result = ft_strjoin(current_val, expanded);
	if (!result)
		return (-1);
	if (env_set(env, key, result) != 0)
	{
		free(result);
		return (-1);
	}
	free(result);
	return (0);
}
