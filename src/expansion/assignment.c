/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:14:49 by radandri          #+#    #+#             */
/*   Updated: 2026/01/22 17:13:57 by radandri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"

int	is_assignment(const char *token)
{
	int	i;
	int	operator_found;

	if (!token || (!ft_isalpha(token[0]) && token[0] != '_'))
		return (0);
	i = 1;
	operator_found = 0;
	while (token[i] && token[i] != '=')
	{
		if (token[i] == '+')
		{
			if (operator_found)
				return (0);
			operator_found = 1;
		}
		else if (!ft_isalnum(token[i]) && token[i] != '_')
			return (0);
		i++;
	}
	return (token[i] == '=');
}

int	split_key_value_assignment(const char *token, char **key, char **value)
{
	char	*equal_sign;
	int		key_len;

	if (!token || !key || !value)
		return (-1);
	equal_sign = ft_strchr(token, '=');
	if (!equal_sign)
		return (-1);
	key_len = equal_sign - token;
	if (key_len > 0 && token[key_len - 1] == '+')
		key_len--;
	*key = ft_substr(token, 0, key_len);
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
