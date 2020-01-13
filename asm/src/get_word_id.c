/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:54:52 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/14 00:07:26 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "op.h"
#include "errors.h"

static int				check_instruction(t_token *cur)
{
	int	i;

	i = 0;
	while (i < OP_COUNT && !((size_t)cur->len == ft_strlen(g_op_tab[i].name)
		&& !ft_strncmp(g_op_tab[i].name, cur->str, cur->len)))
		++i;
	if (i < OP_COUNT)
	{
		cur->op_code = i;
		return (0);
	}
	return (1);
}

static int				check_uint(const char *str, int len)
{
	if (len <= 0)
		return (1);
	while (len && ft_isdigit(*str++))
		--len;
	return (!len);
}

static int				check_int(const char *str, int len)
{
	if (len <= 0)
		return (1);
	if (*str == '-')
		return (check_uint(str + 1, len - 1));
	else
		return (check_uint(str, len));
}

static int				check_label_chars(const char *str, int len)
{
	if (len <= 0)
		return (1);
	while (len && ft_strchr(LABEL_CHARS, *str++))
		--len;
	return (len);
}

enum e_token_word_id	get_word_id(t_token *cur, int line_id)
{
	if (*cur->str == ':'
		&& !check_label_chars(cur->str + 1, cur->len - 1))
		return (I_INDIRECT_LABEL);
	else if (!ft_strncmp(cur->str, "%:", 2)
		&& !check_label_chars(cur->str + 2, cur->len - 2))
		return (I_DIRECT_LABEL);
	else if (!check_int(cur->str, cur->len))
		return (I_INDIRECT);
	else if (*cur->str == '%' && !check_int(cur->str + 1, cur->len - 1))
		return (I_DIRECT);
	else if (*cur->str == 'r' && !check_uint(cur->str + 1, cur->len - 1))
		return (I_REGISTER);
	else if ((cur->len == 5 && !ft_strncmp(cur->str, ".name", cur->len))
		|| (cur->len == 8 && !ft_strncmp(cur->str, ".comment", cur->len)))
		return (I_COMMAND);
	else if (cur->str[cur->len - 1] == ':'
		&& !check_label_chars(cur->str, cur->len - 1))
		return (I_LABEL);
	else if (!check_instruction(cur))
		return (I_INSTRUCTION);
	ft_dprintf(2, "lexer: unknown token '%.*s' at line %d\n",
		cur->len, cur->str, line_id);
	ft_exit(NULL, E_UNKNOWN_TOKEN);
	return (I_NONE);
}
