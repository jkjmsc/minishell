/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:11:15 by radandri          #+#    #+#             */
/*   Updated: 2025/12/16 13:31:47 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_pwd(void)
{
	char	cwd[4096];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
