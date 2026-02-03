/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 06:30:45 by radandri          #+#    #+#             */
/*   Updated: 2026/01/16 06:30:47 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include "errors.h"

void	print_syntax_error(const char *msg)
{
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putendl_fd((char *)msg, 2);
}

void	builtin_error(const char *msg, char *cmd, char *argv)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (argv)
	{
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd("': ", 2);
	}
	else
		ft_putstr_fd(": ", 2);
	ft_putendl_fd((char *)msg, 2);
}
