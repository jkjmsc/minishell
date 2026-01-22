/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:16:36 by radandri          #+#    #+#             */
/*   Updated: 2025/12/16 13:33:23 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_unset(char **args, t_env **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		*env = env_remove(*env, args[i]);
		i++;
	}
	return (0);
}
