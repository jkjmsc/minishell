/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:37:51 by jkarippa          #+#    #+#             */
/*   Updated: 2026/01/21 18:41:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
/*
** Including all the headerfiles required by the utilities
*/
# include "../../lib/libft/libft.h"
# include "../environment/env.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_token	t_token;

/*
** enum datatype for the TYPE for DLL and AST
*/
typedef enum e_node_type
{
	NIL,
	CMD,
	PIPE,
	OR,
	AND,
	AMPERSAND,
	O_SUBSHELL,
	C_SUBSHELL,
	IN_REDIRECTION,
	OUT_REDIRECTION,
	APPEND_REDIRECTION,
	HEREDOC,
	WORD
}						t_node_type;
/*
** Function declarations
*/

int						safe_malloc(void **ret, size_t bytes);
void					terminate(void);
int						get_token_priority(t_node_type type);
int						is_operator(t_node_type type);
t_token					*last_node(t_token *head);
t_token					*skip_subshell_expression(t_token *current);
int						print_syntax_not_implemented(const char *op);
int						validate_token_list(t_token *head);
void					print_tokens(t_token *head);
int						open_redir(t_token *redir, t_token *filename);
void					handle_redirections(t_token *head);
void					close_all_fds(t_token *head);
void					close_fd(t_token *token);
int						is_assignment(const char *token);
int						split_key_value_assignment(const char *token,
							char **key, char **value);
char					*expand_value(const char *value, t_env *env);
int						process_assignment(t_env **env, const char *token);
int						process_compound_assignment(t_env **env,
							const char *token, char *key, char *expanded);
void					process_all_assignments(t_token *head, t_env **env);

#endif