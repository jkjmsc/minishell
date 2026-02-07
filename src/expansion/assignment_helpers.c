/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 06:11:27 by radandri          #+#    #+#             */
/*   Updated: 2026/01/18 03:49:04 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../environment/env.h"
#include "../minishell.h"
#include "expansion/assignment.h"

char	*expand_and_join(char *result, const char *value, int *i, t_env *env)
{
	char	*var;
	char	*tmp;
	char	*var_value;
	int		start;

	start = ++(*i);
	while (ft_isalnum(value[*i]) || value[*i] == '_')
		(*i)++;
	var = ft_substr(value, start, *i - start);
	if (!var)
		return (free(result), NULL);
	var_value = env_get(env, var);
	if (!var_value)
		var_value = "";
	tmp = ft_strjoin(result, var_value);
	free(result);
	free(var);
	return (tmp);
}

char	*append_char(char *result, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(result, buf);
	free(result);
	return (tmp);
}

char	*append_exit_code(char *result, t_minishell *minishell, int *i)
{
	char	*nstr;
	char	*tmp;

	if (!minishell)
	{
		nstr = ft_itoa(0);
	}
	else
		nstr = ft_itoa(minishell->last_exit_code);
	if (!nstr)
		return (NULL);
	tmp = ft_strjoin(result, nstr);
	free(result);
	free(nstr);
	if (!tmp)
		return (NULL);
	*i += 2;
	return (tmp);
}
