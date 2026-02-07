/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 00:00:00 by radandri          #+#    #+#             */
/*   Updated: 2026/02/03 14:37:22 by radandri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HELPERS_H
# define MAIN_HELPERS_H

# include "minishell.h"
# include "tokenization/token.h"

int	handle_token_ret(int ret, t_token **head);
int	handle_eof_and_continue(int ret);
int	apply_redirections(t_token **head, t_minishell *minishell);
int	move_leading_redir_after_cmd(t_token **head, t_token *redir);

#endif
