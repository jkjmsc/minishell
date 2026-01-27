/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 21:00:00 by codespace         #+#    #+#             */
/*   Updated: 2026/01/27 21:00:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment/env.h"
#include "execution/executor.h"
#include "parser/ast.h"
#include "tokenization/token.h"
#include "utils/utils.h"

void	set_exit_code(t_env **env, int exit_code)
{
	char	*exit_code_str;

	exit_code_str = ft_itoa(exit_code);
	if (exit_code_str)
	{
		env_set(env, "?", exit_code_str);
		free(exit_code_str);
	}
}

void	init_shell_env(t_env **env)
{
	char	*exit_code_str;

	exit_code_str = ft_itoa(0);
	if (exit_code_str)
	{
		env_set(env, "?", exit_code_str);
		free(exit_code_str);
	}
}

void	validate_and_set_error(t_token **head, t_env **env,
		int *last_exit_code)
{
	if (!validate_token_list(*head))
		return ;
	terminate_dll(head);
	*last_exit_code = 2;
	set_exit_code(env, *last_exit_code);
}
