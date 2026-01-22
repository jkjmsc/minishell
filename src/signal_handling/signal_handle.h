/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:05:39 by jkarippa          #+#    #+#             */
/*   Updated: 2025/11/17 20:53:23 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLE_H
# define SIGNAL_HANDLE_H
# include "../utils/utils.h"
# include <signal.h>
# include <stdio.h>
/*
** Function declarations
*/

void	signinthandler(int sig_num);
#endif