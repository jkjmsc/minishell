/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 06:11:27 by radandri          #+#    #+#             */
/*   Updated: 2026/01/18 03:49:04 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	restore_stdio(int saved_in, int saved_out)
{
	if (saved_in != -1)
		dup2(saved_in, STDIN_FILENO);
	if (saved_out != -1)
		dup2(saved_out, STDOUT_FILENO);
	if (saved_in != -1)
		close(saved_in);
	if (saved_out != -1)
		close(saved_out);
}
