/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 21:10:20 by jkarippa          #+#    #+#             */
/*   Updated: 2026/01/20 18:49:34 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
/*
** Including all the headerfiles required by the tokenization
*/
# include "../utils/utils.h"

/*
** Structure definition for DLL
*/
typedef struct s_token
{
	char			*value;
	t_node_type		type;
	int				idx;
	int				fd;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

/*
** Helper structure to group parameters and reduce function argument count
*/
typedef struct s_tok_ctx
{
	t_token			**head;
	t_token			**prev;
	char			*token;
	int				*i;
	int				idx;
}					t_tok_ctx;

/*
** Function declarations
*/

int					read_cmdline(char **buffer);
int					read_line_from_fd(int fd, char **result);
int					tokenization(t_token **head);
int					add_token_to_list(t_token **head, t_token **prev,
						char *token, int idx);
int					token_generator(t_token **head, const char *buffer);
t_token				*create_node(void);
void				node_info(int idx, char *buffer, t_token **nxt,
						t_token **prev);
t_node_type			token_type_finder(char *buffer);
int					is_whitespace(const char *c);
int					count_no_of_char(const char *buffer);
void				print_tokens(t_token *head);
void				remove_quote(char **buffer);
void				remove_dquote(char **buffer);
void				terminate_dll(t_token **token);
int					count_char(const char *buffer, const char c);
int					get_operator_len(char c1, char c2);
int					get_operator_len_quoted(char *token, int pos);
char				*alloc_copy_token(char *token, int start, int len);
void				advance_past_quote(char *token, int *i);
char				*mark_tmp_if_needed(char *tmp, int quoted);
int					create_and_link_token(t_token **head, t_token **prev,
						char *tmp, int idx);
int					process_token_string(t_token **head, t_token **prev,
						char *token, int idx);
int					extract_normal_token(char *token, int *i, char **tmp,
						int *len);
#endif