/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 06:30:45 by radandri          #+#    #+#             */
/*   Updated: 2026/01/16 06:30:47 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_env	t_env;

typedef struct s_minishell
{
	t_env				*env;
	int					last_exit_code;
}						t_minishell;

#endif
