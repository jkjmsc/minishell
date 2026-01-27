/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:46:04 by jkarippa          #+#    #+#             */
/*   Updated: 2026/01/21 18:35:32 by radandri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment/env.h"
#include "execution/executor.h"
#include "parser/ast.h"
#include "signal_handling/signal_handle.h"
#include "tokenization/token.h"
#include "utils/utils.h"

static int	handle_token_ret(int ret, t_token **head)
{
	if (ret == 1)
		return (1);
	if (ret == -1)
	{
		printf("minishell: syntax error: unclosed quote\n");
		terminate_dll(head);
		return (1);
	}
	printf("minishell: tokenization error\n");
	return (-1);
}

static int	handle_eof_and_continue(int ret)
{
	if (ret == 1)
	{
		if (isatty(STDIN_FILENO))
			printf("Exit minishell.\n");
		return (1);
	}
	return (0);
}

static void	process_command(t_token **head, t_env **env, int *last_exit_code)
{
	t_ast	*ast;
	t_token	*tail;
	char	*exit_code_str;

	if (validate_token_list(*head))
	{
		terminate_dll(head);
		return ;
	}
	tail = last_node(*head);
	ast = ast_build(*head, tail, *env);
	if (!ast)
	{
		terminate_dll(head);
		return ;
	}
	handle_redirections(*head);
	*last_exit_code = execute_ast(ast, env);
	exit_code_str = ft_itoa(*last_exit_code);
	if (exit_code_str)
	{
		env_set(env, "?", exit_code_str);
		free(exit_code_str);
	}
	close_all_fds(*head);
	terminate_dll(head);
}

static int	run_shell_loop(t_env **env)
{
	t_token	*head;
	int		last_exit_code;
	int		ret;
	int		action;
	char	*exit_code_str;

	last_exit_code = 0;
	exit_code_str = ft_itoa(0);
	if (exit_code_str)
	{
		env_set(env, "?", exit_code_str);
		free(exit_code_str);
	}
	while (1)
	{
		head = NULL;
		ret = tokenization(&head);
		if (ret != 0)
		{
			action = handle_token_ret(ret, &head);
			if (action == 1 && handle_eof_and_continue(ret))
				break ;
			if (action != 1)
				break ;
			continue ;
		}
		process_command(&head, env, &last_exit_code);
	}
	terminate_dll(&head);
	clear_history();
	return (last_exit_code);
}

int	main(int ac, char **argv, char **envp)
{
	t_env	*env;

	(void)argv;
	if (ac > 1)
	{
		printf("\033[31mArguments are not required for execution.\033[0m\n");
		return (EXIT_FAILURE);
	}
	env = env_init(envp);
	if (!env)
		return (EXIT_FAILURE);
	env_update_shlvl(&env);
	rl_catch_signals = 0;
	signal(SIGINT, signinthandler);
	signal(SIGQUIT, SIG_IGN);
	return (run_shell_loop(&env));
}

// int	main(void)
// {
// 	char	*c;

// 	c = NULL;
// 	if (!safe_malloc((void **)&c, sizeof(char) * 3))
// 		printf("No errors for defining 3 bytes\n");
// 	else
// 		printf("ERROR!!\n");
// 	free(c);
// 	return (0);
// }