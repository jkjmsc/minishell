/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:01:54 by jkarippa          #+#    #+#             */
/*   Updated: 2025/07/15 14:24:57 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The function creates a new list with the list provided and manupulated by the
// function provided. However it will delete the list if it comes across NULL.
// Added a new line to check if the content to be inserted is NULL or not!
// Due to the memory leak that arised from lstmap execution.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*current;
	void	*new_content;

	current = NULL;
	if (!lst)
		return (NULL);
	else
	{
		while (lst)
		{
			new_content = f(lst->content);
			new = ft_lstnew(new_content);
			if (new == NULL)
			{
				del(new_content);
				ft_lstclear(&current, (*del));
				return (NULL);
			}
			ft_lstadd_back(&current, new);
			lst = lst->next;
		}
	}
	return (current);
}
