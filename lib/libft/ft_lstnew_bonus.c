/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:26:21 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 14:31:23 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function copies the input parameter to the content inside the node.
// This function should work even if the content is NULL.
t_list	*ft_lstnew(void *content)
{
	t_list	*current;

	current = (t_list *)malloc(sizeof(struct s_list));
	if (current == NULL)
		return (NULL);
	current->content = content;
	current->next = NULL;
	return (current);
}
