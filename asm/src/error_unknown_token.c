/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_unknown_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:09:35 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/14 15:14:16 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errors.h"

void	error_unknown_token(int len, const char *str, int line_id)
{
	ft_dprintf(2, "lexer: unknown token '%.*s' at line %d\n", len, str, line_id);
	ft_exit(NULL, E_UNKNOWN_TOKEN);
}
