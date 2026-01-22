/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:33:27 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 14:32:49 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function basically counts the no.of nodes in the list
int	ft_lstsize(t_list *lst)
{
	unsigned long	len;
	t_list			*current;

	current = lst;
	len = 0;
	while (current != NULL)
	{
		current = current->next;
		len++;
	}
	return (len);
}
