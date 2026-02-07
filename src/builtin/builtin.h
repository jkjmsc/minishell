/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:07:26 by jkarippa          #+#    #+#             */
/*   Updated: 2026/02/07 17:07:30 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../environment/env.h"
# include "../minishell.h"
# include "../utils/utils.h"

/*
** Builtin command declarations
*/
int		count_argv(char **argv);
int		ft_exit(int argc, char **argv);
int		ft_echo(char **argv);
int		ft_env(t_env *env, int argc, char **argv);
int		ft_pwd(void);
int		ft_unset(char **args, t_env **env);
int		ft_cd(int argc, char **argv, t_env **envp);
int		ft_export(int argc, char **argv, t_minishell *minishell);
char	*expand_tilde(char *path, t_env *env);
void	print_export_env(t_env *env);
void	sort_env_tab(char **env);
void	handle_export_append(const char *arg, char *equal_sign, t_env **env);
void	handle_export_assign(const char *arg, char *equal_sign, t_env **env);
#endif
