/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:09:59 by jkarippa          #+#    #+#             */
/*   Updated: 2026/02/07 17:10:02 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/main_helpers.h"
#include "utils/utils.h"

int	handle_token_ret(int ret, t_token **head)
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

int	handle_eof_and_continue(int ret)
{
	if (ret == 1)
	{
		if (isatty(STDIN_FILENO))
			printf("Exit minishell.\n");
		return (1);
	}
	return (0);
}

int	apply_redirections(t_token **head, t_minishell *minishell)
{
	int	ret;

	ret = handle_redirections(*head);
	if (ret == 0)
		return (0);
	minishell->last_exit_code = 1;
	if (ret == -2)
		minishell->last_exit_code = 2;
	close_all_fds(*head);
	terminate_dll(head);
	return (1);
}

/*
** Detach redirection and insert it after 'end'.
*/
void	detach_and_insert_after(t_token **head, t_token *redir,
				t_token *filename, t_token *end)
{
	if (!redir || !filename || !end)
		return ;
	redir->next = filename->next;
	if (filename->next)
		filename->next->prev = redir;
	if (redir->prev)
		redir->prev->next = redir->next;
	if (*head == redir)
		*head = redir->next;
	filename->prev = end;
	redir->prev = end;
	filename->next = end->next;
	redir->next = filename;
	end->next = redir;
	if (filename->next)
		filename->next->prev = filename;
}

/*
** Move a single leading redirection and its filename after the following
** command segment. Returns 1 on success, 0 otherwise.
*/
int	move_leading_redir_after_cmd(t_token **head, t_token *redir)
{
	t_token	*filename;
	t_token	*cmd;
	t_token	*end;

	if (!redir || !redir->next)
		return (0);
	filename = redir->next;
	if (!filename || filename->type != WORD || !filename->next
		|| filename->next->type != WORD)
		return (0);
	cmd = filename->next;
	end = cmd;
	while (end->next && !is_operator(end->next->type))
		end = end->next;
	detach_and_insert_after(head, redir, filename, end);
	return (1);
}
