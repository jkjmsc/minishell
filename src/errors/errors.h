/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 06:30:07 by radandri          #+#    #+#             */
/*   Updated: 2026/01/16 06:30:10 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <stdio.h>

# define NOT_A_VALID_IDENTIFIER "not a valid identifier"
# define TOO_MANY_ARG "too many arguments"
# define NO_SUCH_FILE_DIRECTORY "No such file or directory"

void	builtin_error(const char *msg, char *cmd, char *arg);

#endif