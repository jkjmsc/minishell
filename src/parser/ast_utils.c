/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:36:16 by radandri          #+#    #+#             */
/*   Updated: 2026/01/20 06:22:51 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../environment/env.h"
#include "ast.h"
#include "../builtin/builtin.h"
/*
** we need to know the numbers of tokens
** between 2 segment (start-> end) for argv
*/
int	count_tokens_range(t_token *start, t_token *end)
{
	t_token	*current;
	int		count;

	count = 0;
	current = start;
	while (current != end->next)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	*expand_token(char *token, t_env *env)
{
	if (!token || !token[0])
		return (ft_strdup(""));
	if (token[0] == '~' && (token[1] == '\0' || token[1] == '/'))
		return (expand_tilde(token, env));
	return (ft_strdup(token));
}

/*
** convert tokens into an array
** should return an allocated char**
** Example:
** ["echo"]["hello"]['world] -> argv = {"echo", "hello", "world", NULL}
**
*/
char	**tokens_to_argv(t_token *start, t_token *end, t_env *env)
{
	int		n;
	char	**argv;
	int		i;
	t_token	*current;

	n = count_tokens_range(start, end);
	argv = NULL;
	i = 0;
	current = start;
	safe_malloc((void **)&argv, sizeof(char *) * (n + 1));
	while (current != end->next)
	{
		argv[i++] = expand_token(current->value, env);
		current = current->next;
	}
	argv[i] = NULL;
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
		{
			free(node->cmd_args[i]);
			i++;
		}
		free(node->cmd_args);
	}
	if (node->filename)
		free(node->filename);
	free(node);
}
