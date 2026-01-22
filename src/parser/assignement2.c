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
#include "../utils/utils.h"
#include "../../lib/libft/libft.h"

int					is_numeric(const char *str);
char				*apply_subtract_op(const char *current_val,
						const char *expanded);
char				*apply_mult_op(const char *current_val,
						const char *expanded);
char				*apply_div_mod_op(const char *current_val,
						const char *expanded, char op);

static char	get_assignment_operator(const char *token)
{
	int	i;

	i = 0;
	while (token[i] && token[i] != '=')
		i++;
	if (i > 0 && (token[i - 1] == '+' || token[i - 1] == '-'
			|| token[i - 1] == '*' || token[i - 1] == '/'
			|| token[i - 1] == '%'))
		return (token[i - 1]);
	return ('=');
}

static char	*apply_compound_op(const char *current_val, const char *expanded,
		char op)
{
	if (op == '+')
		return (ft_strjoin(current_val, expanded));
	if (op == '-')
		return (apply_subtract_op(current_val, expanded));
	if (op == '*')
		return (apply_mult_op(current_val, expanded));
	if (op == '/' || op == '%')
		return (apply_div_mod_op(current_val, expanded, op));
	return (ft_strdup(expanded));
}

int	process_compound_assignment(t_env **env, const char *token, char *key,
		char *expanded)
{
	char	*current_val;
	char	*result;
	char	op;

	op = get_assignment_operator(token);
	if (op == '=')
	{
		if (env_set(env, key, expanded) != 0)
			return (-1);
		return (0);
	}
	current_val = env_get(*env, key);
	if (!current_val)
		current_val = "";
	result = apply_compound_op(current_val, expanded, op);
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
