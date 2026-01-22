/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:14:49 by radandri          #+#    #+#             */
/*   Updated: 2026/01/21 18:28:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../environment/env.h"
#include "../utils/utils.h"

int	is_assignment(const char *token)
{
	int	i;

	if (!token || (!ft_isalpha(token[0]) && token[0] != '_'))
		return (0);
	i = 1;
	while (token[i] && token[i] != '=')
	{
		if (!ft_isalnum(token[i]) && token[i] != '_')
			return (0);
		i++;
	}
	return (token[i] == '=');
}

int	split_key_value_assignment(const char *token, char **key, char **value)
{
	char	*equal_sign;

	if (!token || !key || !value)
		return (-1);
	equal_sign = ft_strchr(token, '=');
	if (!equal_sign)
		return (-1);
	*key = ft_substr(token, 0, equal_sign - token);
	*value = ft_strdup(equal_sign + 1);
	if (!*key || !*value)
	{
		free(*key);
		free(*value);
		*key = NULL;
		*value = NULL;
		return (-1);
	}
	return (0);
}

static char	*expand_and_join(char *result, const char *value, int *i,
		t_env *env)
{
	char	*var;
	char	*tmp;
	int		start;

	start = ++(*i);
	while (ft_isalnum(value[*i]) || value[*i] == '_')
		(*i)++;
	var = ft_substr(value, start, *i - start);
	if (!var)
		return (free(result), NULL);
	tmp = ft_strjoin(result, env_get(env, var));
	free(result);
	free(var);
	return (tmp);
}

static char	*append_char(char *result, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(result, buf);
	free(result);
	return (tmp);
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
		if (value[i] == '$' && (ft_isalpha(value[i + 1]) || value[i
					+ 1] == '_'))
			tmp = expand_and_join(result, value, &i, env);
		else
			tmp = append_char(result, value[i++]);
		if (!tmp)
			return (NULL);
		result = tmp;
	}
	return (result);
}
