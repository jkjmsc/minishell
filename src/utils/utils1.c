/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarippa <jkarippa@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:09:18 by jkarippa          #+#    #+#             */
/*   Updated: 2025/12/12 18:28:03 by jkarippa       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenization/token.h"
#include "utils.h"

/*
** Utility wrapper function for safe allocation of malloc
** How to use example for the syntax:
** 									if (!safe_malloc((void **)&c, sizeof(char)
* 3))
*/
int	safe_malloc(void **ret, size_t bytes)
{
	*ret = malloc(bytes);
	if (*ret == NULL)
	{
		printf("\033[31mError with malloc\n\033[0m");
		return (1);
	}
	return (0);
}

// int	main(void)
// {
// 	char	*c;

// 	c = NULL;
// 	if (!safe_malloc((void **)&c, sizeof(char) * 3))
// 		printf("No errors for defining 3 bytes\n");
// 	else
// 		printf("ERROR!!\n");
// 	free(c);
// 	return (0);
// }

/*
** Print a standardized "not implemented" syntax error for unsupported
** operators. Message is printed to stderr to match shell error behaviour.
** Returns 1 when an error was printed, 0 otherwise.
*/
int	print_syntax_not_implemented(const char *op)
{
	if (op == NULL)
		return (0);
	fprintf(stderr, "minishell: syntax error: %s not implemented\n", op);
	return (1);
}

const char	*print_type_node_by_int(int type)
{
	if (type == 1)
		return ("CMD");
	else if (type == 2)
		return ("PIPE");
	else if (type == 3)
		return ("OR");
	else if (type == 4)
		return ("AND");
	else if (type == 5)
		return ("AMPERSAND");
	else if (type == 6)
		return ("O_SUBSHELL");
	else if (type == 7)
		return ("C_SUBSHELL");
	else if (type == 8)
		return ("IN_REDIRECTION");
	else if (type == 9)
		return ("OUT_REDIRECTION");
	else if (type == 10)
		return ("APPEND_REDIRECTION");
	else if (type == 11)
		return ("HEREDOC");
	else if (type == 12)
		return ("WORD");
	return ("UNKNOWN");
}

void	print_tokens(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	printf("Token List:\n");
	while (tmp)
	{
		printf("  idx: %d | type: %s | value: [%s] | fd: [%d]\n", tmp->idx,
			print_type_node_by_int(tmp->type), tmp->value, tmp->fd);
		tmp = tmp->next;
	}
}
