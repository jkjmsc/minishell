/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:15:37 by jkarippa          #+#    #+#             */
/*   Updated: 2026/02/07 17:15:48 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../environment/env.h"
#include <unistd.h>

void	ft_free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*check_cmd_in_dir(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full)
		return (NULL);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

static char	*search_in_dirs(char **dirs, char *cmd)
{
	int		i;
	char	*result;

	i = 0;
	while (dirs[i])
	{
		result = check_cmd_in_dir(dirs[i], cmd);
		if (result)
		{
			ft_free_split(dirs);
			return (result);
		}
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}

char	*find_path(char *cmd, t_env *env)
{
	char	*path;
	char	**dirs;
	char	*result;

	if (!cmd || !env)
		return (NULL);
	path = (char *)env_get(env, "PATH");
	if (!path || path[0] == '\0')
	{
		result = check_cmd_in_dir(".", cmd);
		if (result)
			return (result);
		return (NULL);
	}
	path = ft_strdup(path);
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	free(path);
	if (!dirs)
		return (NULL);
	return (search_in_dirs(dirs, cmd));
}
