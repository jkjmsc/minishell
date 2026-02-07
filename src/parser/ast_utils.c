/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:36:16 by radandri          #+#    #+#             */
/*   Updated: 2026/02/05 21:06:19 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin/builtin.h"
#include "../environment/env.h"
#include "../utils/utils.h"
#include "ast.h"

#define MARKER_DOUBLE_QUOTE '\x01'
#define MARKER_SINGLE_QUOTE '\x02'

/*
** we need to know the numbers of tokens
** between 2 segment (start-> end) for argv
*/
char			*expand_token(char *token, t_minishell *minishell);

static char	*join_and_free(char *acc, char *part)
{
	char	*tmp;

	tmp = ft_strjoin(acc, part);
	free(part);
	free(acc);
	return (tmp);
}

static char	*build_arg_from_group(t_token **current, t_token *end,
		t_minishell *minishell, int *has_quote)
{
	char	*acc;
	char	*part;
	int		group_idx;

	acc = ft_strdup("");
	if (!acc)
		return (NULL);
	group_idx = (*current)->idx;
	while (*current && *current != end->next && (*current)->idx == group_idx)
	{
		if ((*current)->value && ((*current)->value[0] == MARKER_SINGLE_QUOTE
				|| (*current)->value[0] == MARKER_DOUBLE_QUOTE))
			*has_quote = 1;
		part = expand_token((*current)->value, minishell);
		if (!part)
			return (free(acc), NULL);
		acc = join_and_free(acc, part);
		if (!acc)
			return (NULL);
		*current = (*current)->next;
	}
	return (acc);
}

static int	fill_argv(t_token *first, t_token *end, t_minishell *minishell,
		char **argv)
{
	int		i;
	int		has_quote;

	i = 0;
	while (first && first != end->next)
	{
		has_quote = 0;
		argv[i] = build_arg_from_group(&first, end, minishell, &has_quote);
		if (!argv[i])
			return (-1);
		if (!has_quote && argv[i][0] == '\0')
		{
			free(argv[i]);
			continue ;
		}
		i++;
	}
	return (i);
}

/*
** convert tokens into an array
** should return an allocated char**
** Example:
** ["echo"]["hello"]['world] -> argv = {"echo", "hello", "world", NULL}
*/
char	**tokens_to_argv(t_token *start, t_token *end, t_minishell *minishell)
{
	char	**argv;
	int		n;
	t_token	*first;

	first = start;
	while (first && first != end->next && is_assignment(first->value))
		first = first->next;
	n = 0;
	if (first && first != end->next)
		n = end->idx - first->idx + 1;
	if (safe_malloc((void **)&argv, sizeof(char *) * (n + 1)))
		return (NULL);
	n = fill_argv(first, end, minishell, argv);
	if (n < 0)
		return (NULL);
	argv[n] = NULL;
	return (argv);
}

/*
** recursively frees an entire ast in a post order
*/
void	free_ast(t_ast *node)
{
	int	i;

	if (node == NULL)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->cmd_args)
	{
		i = 0;
		while (node->cmd_args[i])
			free(node->cmd_args[i++]);
		free(node->cmd_args);
	}
	if (node->prefix_env)
	{
		i = 0;
		while (node->prefix_env[i])
			free(node->prefix_env[i++]);
		free(node->prefix_env);
	}
	if (node->filename)
		free(node->filename);
	free(node);
}
