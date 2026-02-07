/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 06:11:27 by radandri          #+#    #+#             */
/*   Updated: 2026/02/04 02:50:00 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSIGNMENT_H
# define ASSIGNMENT_H

# include "../environment/env.h"
# include "../minishell.h"

char			*expand_and_join(char *result, const char *value, int *i,
					t_env *env);
char			*append_char(char *result, char c);
char			*append_exit_code(char *result, t_minishell *minishell, int *i);

typedef struct s_expand_state
{
	const char	*value;
	char		*result;
	int			i;
	int			in_single;
	int			in_double;
	int			track_quotes;
	t_minishell	*minishell;
}				t_expand_state;

#endif
