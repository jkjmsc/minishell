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

/*
** Validate token list for unsupported operators (&&, ||, (), &).
** Returns 1 if an unsupported operator was found and error printed.
** Returns 0 if all tokens are valid.
*/
int	validate_token_list(t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr != NULL)
	{
		if (curr->type == AND && print_syntax_not_implemented("&&"))
			return (1);
		if (curr->type == OR && print_syntax_not_implemented("||"))
			return (1);
		if ((curr->type == O_SUBSHELL || curr->type == C_SUBSHELL)
			&& print_syntax_not_implemented("()"))
			return (1);
		if (curr->type == AMPERSAND && print_syntax_not_implemented("&"))
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	print_tokens(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	printf("Token List:\n");
	while (tmp)
	{
		printf("  idx: %d | type: %d | value: [%s] | fd: [%d]\n", tmp->idx,
			tmp->type, tmp->value, tmp->fd);
		tmp = tmp->next;
	}
}
