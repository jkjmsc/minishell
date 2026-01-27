/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:00:00 by radandri          #+#    #+#             */
/*   Updated: 2026/01/27 19:46:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment/env.h"
#include "../../lib/libft/libft.h"

char	*expand_and_join(char *result, const char *value, int *i, t_env *env);
char	*append_char(char *result, char c);

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

char	*expand_value(const char *value, t_env *env)
{
	char	*result;
	char	*tmp;
	int		i;

	if (!value)
		return (ft_strdup(""));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && (ft_isalpha(value[i + 1]) || value[i + 1] == '_'
				|| value[i + 1] == '?'))
			tmp = expand_and_join(result, value, &i, env);
		else
			tmp = append_char(result, value[i++]);
		if (!tmp)
			return (NULL);
		result = tmp;
	}
	return (result);
}
