/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 21:21:42 by radandri          #+#    #+#             */
/*   Updated: 2026/01/21 00:21:36 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../environment/env.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	cd_error(char *msg, char *oldpwd)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putendl_fd(msg, 2);
	if (oldpwd)
		free(oldpwd);
	return (1);
}

static void	update_pwd_vars(t_env **envp, char *oldpwd)
{
	char	*newpwd;

	if (oldpwd)
		env_set(envp, "OLDPWD", oldpwd);
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		env_set(envp, "PWD", newpwd);
		free(newpwd);
	}
}

/*
** expand ~ to HOME directory
** 1. ~ -> /home/user
** 2. ~/docs -> /home/user/docs
** if HOME not set, return copy of token eg: ~ -> ~
*/
char	*expand_tilde(char *path, t_env *env)
{
	char	*home;
	char	*expanded;

	if (!path || path[0] != '~')
		return (path);
	home = env_get(env, "HOME");
	if (!home)
		return (NULL);
	if (path[1] == '\0')
		return (home);
	if (path[1] == '/')
	{
		expanded = ft_strjoin(home, path + 1);
		return (expanded);
	}
	return (path);
}

static char	*get_target_path(int argc, char **argv, t_env *env)
{
	char	*path;

	if (argc == 1)
		return (env_get(env, "HOME"));
	if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		path = env_get(env, "OLDPWD");
		if (path)
			ft_putendl_fd(path, 1);
		return (path);
	}
	return (expand_tilde(argv[1], env));
}

int	ft_cd(int argc, char **argv, t_env **envp)
{
	char	*path;
	char	*oldpwd;
	int		should_free;

	if (argc > 2)
		return (cd_error("too many arguments", NULL));
	oldpwd = getcwd(NULL, 0);
	path = get_target_path(argc, argv, *envp);
	if (!path)
		return (cd_error("HOME not set", oldpwd));
	should_free = (argc > 1 && argv[1][0] == '~' && path != argv[1]);
	if (chdir(path) != 0)
	{
		if (should_free)
			free(path);
		return (cd_error(strerror(errno), oldpwd));
	}
	update_pwd_vars(envp, oldpwd);
	free(oldpwd);
	if (should_free)
		free(path);
	return (0);
}
