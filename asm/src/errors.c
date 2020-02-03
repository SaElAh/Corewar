/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:12:02 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/03 16:37:55 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errors.h"

void	error_unknown_token(int len, const char *str, int line_id)
{
	ft_dprintf(2, "lexer: unknown token '%.*s' at line %d\n",
		len, str, line_id + 1);
	ft_exit(NULL, E_UNKNOWN_TOKEN);
}

void	error_unexpected_token(int len, const char *str, int line_id)
{
	ft_dprintf(2, "parser: unexpected token '%.*s' at line %d\n",
		len, str, line_id);
	ft_exit(NULL, E_UNEXPECTED_TOKEN);
}

void	error_command_without_argument(int len, const char *str, int line_id)
{
	ft_dprintf(2, "parser: command '%.*s' has no argument at line %d\n",
		len, str, line_id);
	ft_exit(NULL, E_COMMAND_WITHOUT_ARGUMENT);
}
