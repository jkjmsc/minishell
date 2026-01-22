/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:00:00 by jkarippa        #+#    #+#             */
/*   Updated: 2025/12/12 12:00:00 by jkarippa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../environment/env.h"
# include "../utils/utils.h"

/*
** Builtin command declarations
*/
int		count_argv(char **argv);
int		ft_exit(t_token *head, int argc, char **argv);
int		ft_echo(char **argv);
int		ft_env(t_env *env);
int		ft_pwd(void);
int		ft_unset(char **args, t_env **env);
int		ft_cd(int argc, char **argv, t_env **envp);
int		ft_export(int argc, char **argv, t_env **env);
char	*expand_tilde(char *path, t_env *env);
#endif
