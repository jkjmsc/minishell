/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:26:42 by jkarippa          #+#    #+#             */
/*   Updated: 2025/11/14 21:00:54 by jkarippa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/*
** Remove only the outermost matching double quotes if they enclose the string.
** This preserves single quotes inside double quotes (bash behavior).
*/
void	remove_dquote(char **buffer)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	if (!buffer || !*buffer)
		return ;
	str = *buffer;
	len = ft_strlen(str);
	if (len < 2 || str[0] != '\"' || str[len - 1] != '\"')
		return ;
	i = 1;
	j = 0;
	while (i < len - 1)
	{
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}

/*
** Remove only the outermost matching single quotes if they enclose the string.
** This preserves everything else literally (bash behavior).
*/
void	remove_quote(char **buffer)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	if (!buffer || !*buffer)
		return ;
	str = *buffer;
	len = ft_strlen(str);
	if (len < 2 || str[0] != '\'' || str[len - 1] != '\'')
		return ;
	i = 1;
	j = 0;
	while (i < len - 1)
	{
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}

/*
** Function to free all the allocations related to DLL
*/
void	terminate_dll(t_token **token)
{
	t_token	*curr;
	t_token	*nxt;

	curr = *token;
	while (curr)
	{
		free(curr->value);
		nxt = curr->next;
		free(curr);
		curr = nxt;
	}
}

/*
** Function to check whether there exist odd
** or even number of a specific character.
*/
int	count_char(const char *buffer, const char c)
{
	int	count;
	int	i;

	if (!buffer)
		return (0);
	count = 0;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == c)
			count++;
		i++;
	}
	return (count);
}
