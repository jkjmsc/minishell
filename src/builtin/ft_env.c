/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:11:39 by radandri          #+#    #+#             */
/*   Updated: 2026/01/16 05:51:53 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** Print all environnement variables
** Example:
**   $ env
**   PATH=/usr/bin:/bin
**   HOME=/home/user
**   SHLVL=2
*/
int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
