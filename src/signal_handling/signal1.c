/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:57:51 by jkarippa          #+#    #+#             */
/*   Updated: 2025/11/17 22:53:13 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handle.h"

void	signinthandler(int sig_num)
{
	(void)sig_num;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
