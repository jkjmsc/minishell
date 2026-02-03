/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 05:14:49 by radandri          #+#    #+#             */
/*   Updated: 2026/01/20 05:33:53 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../environment/env.h"
# include "../minishell.h"
# include "../tokenization/token.h"

# define MARKER_DOUBLE_QUOTE '\x01'
# define MARKER_SINGLE_QUOTE '\x02'

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**cmd_args;
	char			*filename;
	char			**prefix_env;
}					t_ast;

void				print_ast(t_ast *node, int depth);
int					depth_tree(t_ast *root);
t_token				*find_lowest_precedence_operator(t_token *head,
						t_token *tail);
t_ast				*create_ast_node(t_node_type type);
t_ast				*create_command_node(t_token *start, t_token *end,
						t_minishell *minishell);
t_ast				*ast_build(t_token *head, t_token *tail,
						t_minishell *minishell);
int					count_tokens_range(t_token *start, t_token *end);
char				**tokens_to_argv(t_token *start, t_token *end,
						t_minishell *minishell);
char				**get_prefix_assignments(t_token *start, t_token *end);
void				update_lowest_operator(t_token **lowest, t_token *current);
char				*remove_literal_quotes(char *str);
char				*expand_token(char *token, t_minishell *minishell);

void				free_ast(t_ast *node);

#endif