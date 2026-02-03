/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignement.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 06:11:27 by radandri          #+#    #+#             */
/*   Updated: 2026/01/18 03:49:04 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSIGNEMENT_H
# define ASSIGNEMENT_H

# include "../environment/env.h"
# include "../minishell.h"

char	*expand_and_join(char *result, const char *value, int *i, t_env *env);
char	*append_char(char *result, char c);
char	*append_exit_code(char *result, t_minishell *minishell, int *i);

#endif
