/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:18:19 by jkarippa          #+#    #+#             */
/*   Updated: 2026/02/07 17:18:21 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "../environment/env.h"

char	**get_prefix_assignments(t_token *start, t_token *end)
{
	char	**assignments;
	int		count;
	int		i;
	t_token	*current;

	count = 0;
	current = start;
	while (current != end->next && is_assignment(current->value))
	{
		count++;
		current = current->next;
	}
	if (count == 0)
		return (NULL);
	safe_malloc((void **)&assignments, sizeof(char *) * (count + 1));
	i = 0;
	current = start;
	while (current != end->next && is_assignment(current->value))
	{
		assignments[i++] = ft_strdup(current->value);
		current = current->next;
	}
	assignments[i] = NULL;
	return (assignments);
}

void	update_lowest_operator(t_token **lowest, t_token *current)
{
	int	current_priority;
	int	lowest_priority;

	current_priority = get_token_priority(current->type);
	if (*lowest == NULL)
	{
		*lowest = current;
		return ;
	}
	lowest_priority = get_token_priority((*lowest)->type);
	if (current_priority >= lowest_priority)
		*lowest = current;
}
