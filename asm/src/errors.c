/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:12:02 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/15 18:13:33 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errors.h"

void	error_unknown_token(int len, const char *str, int line_id)
{
	ft_dprintf(2, "lexer: unknown token '%.*s' at line %d\n",
		len, str, line_id);
	ft_exit(NULL, E_UNKNOWN_TOKEN);
}

//TODO: add expected token name here to help debugging (from main.c)
void	error_unexpected_token(int len, const char *str, int line_id)
{
	ft_dprintf(2, "parser: unexpected token '%.*s' at line %d\n",
		len, str, line_id);
	ft_exit(NULL, E_UNEXPECTED_TOKEN);
}
