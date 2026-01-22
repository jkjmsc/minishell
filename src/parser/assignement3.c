/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 00:00:00 by radandri          #+#    #+#             */
/*   Updated: 2026/01/22 00:00:00 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"

int	is_numeric(const char *str)
{
	int	i;
	int	min_len;

	if (!str || !str[0])
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	else
		i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (str[0] == '-' || str[0] == '+')
		min_len = 1;
	else
		min_len = 0;
	return (i > min_len);
}

char	*apply_subtract_op(const char *current_val, const char *expanded)
{
	long	num1;
	long	num2;

	if (!is_numeric(current_val) || !is_numeric(expanded))
		return (ft_strdup(expanded));
	num1 = ft_atoi(current_val);
	num2 = ft_atoi(expanded);
	return (ft_itoa(num1 - num2));
}

char	*apply_mult_op(const char *current_val, const char *expanded)
{
	long	num1;
	long	num2;

	if (!is_numeric(current_val) || !is_numeric(expanded))
		return (ft_strdup(expanded));
	num1 = ft_atoi(current_val);
	num2 = ft_atoi(expanded);
	return (ft_itoa(num1 * num2));
}

char	*apply_div_mod_op(const char *current_val, const char *expanded,
		char op)
{
	long	num1;
	long	num2;

	if (!is_numeric(current_val) || !is_numeric(expanded))
		return (ft_strdup(expanded));
	num2 = ft_atoi(expanded);
	if (num2 == 0)
		return (ft_strdup("0"));
	num1 = ft_atoi(current_val);
	if (op == '/')
		return (ft_itoa(num1 / num2));
	return (ft_itoa(num1 % num2));
}
