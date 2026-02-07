/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:10:33 by jkarippa          #+#    #+#             */
/*   Updated: 2026/02/07 17:10:37 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/main_helpers.h"
#include "environment/env.h"
#include "execution/executor.h"
#include "minishell.h"
#include "parser/ast.h"
#include "signal_handling/signal_handle.h"
#include "tokenization/token.h"
#include "utils/utils.h"
#include <unistd.h>

/*
** Move a single leading redirection and its filename after the following
** command segment. Returns 1 on success, 0 otherwise.
*/

/*
** Normalize leading redirections by moving them after the first following
** command segment so they apply to the intended command.
*/
static void	normalize_leading_redirections(t_token **head)
{
	t_token	*curr;

	if (!head || !*head)
		return ;
	curr = *head;
	while (curr && is_operator(curr->type) && (curr->type == IN_REDIRECTION
			|| curr->type == OUT_REDIRECTION
			|| curr->type == APPEND_REDIRECTION) && curr->prev == NULL)
	{
		if (!move_leading_redir_after_cmd(head, curr))
			break ;
		curr = *head;
	}
}

/*
** Process the token list: validate, normalize leading redirections, build
** the AST and execute, updating minishell->last_exit_code.
** Returns 1 if the shell should exit (non-interactive syntax error),
	0 otherwise.
*/
static int	process_command(t_token **head, t_minishell *minishell)
{
	t_ast	*ast;
	t_token	*tail;

	if (validate_token_list(*head))
	{
		minishell->last_exit_code = 2;
		terminate_dll(head);
		if (!isatty(STDIN_FILENO))
			return (1);
		return (0);
	}
	normalize_leading_redirections(head);
	tail = last_node(*head);
	ast = ast_build(*head, tail, minishell);
	if (!ast)
	{
		terminate_dll(head);
		return (0);
	}
	minishell->last_exit_code = execute_ast(ast, minishell);
	close_all_fds(*head);
	free_ast(ast);
	terminate_dll(head);
	return (0);
}

static int	run_shell_loop(t_minishell *minishell)
{
	t_token	*head;
	int		ret;
	int		action;

	while (1)
	{
		head = NULL;
		ret = tokenization(&head);
		if (ret != 0)
		{
			action = handle_token_ret(ret, &head);
			if (action == -1)
				break ;
			if (action == 1 && handle_eof_and_continue(ret))
				break ;
			if (action == 1)
				continue ;
		}
		if (process_command(&head, minishell))
			break ;
	}
	terminate_dll(&head);
	rl_clear_history();
	return (minishell->last_exit_code);
}

int	main(int ac, char **argv, char **envp)
{
	t_minishell	*minishell;
	int			ret;

	if (ac > 1)
	{
		printf("\033[31mArguments are not required for execution.\033[0m\n");
		return (EXIT_FAILURE);
	}
	safe_malloc((void **)&minishell, sizeof(t_minishell));
	(void)argv;
	minishell->env = env_init(envp);
	if (!minishell->env)
		return (EXIT_FAILURE);
	env_update_shlvl(&minishell->env);
	rl_catch_signals = 0;
	signal(SIGINT, signinthandler);
	signal(SIGQUIT, SIG_IGN);
	ret = run_shell_loop(minishell);
	env_free(minishell->env);
	free(minishell);
	return (ret);
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