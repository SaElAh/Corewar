/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 21:43:17 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/18 00:50:28 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_asmdata.h"
#include "errors.h"

static void	expect_end(t_asmdata *adat, int op_ref, t_list *tokens, int line)
{
	int		op_code;
	t_token	*cur;

	op_code = adat->ops[op_ref].op_code;
	if (adat->ops[op_ref].argc < g_op_tab[op_code - 1].argc)
	{
		ft_dprintf(2, "parser: missing arguments for instruction '%s' at \
			line %d\n", g_op_tab[op_code - 1].name, line + 1);
		ft_exit(NULL, E_MISSING_ARGUMENTS);
	}
	else if (tokens->next)
	{
		cur = tokens->next->content;
		error_unexpected_token(cur->len, cur->str, line + 1);
	}
}

static int	expect_arg(t_asmdata *adat, int op_ref, t_token *cur, int line)
{
	unsigned int	*argc;
	int				op_code;
	char			arg_types;

	op_code = adat->ops[op_ref].op_code;
	argc = &adat->ops[op_ref].argc;
	arg_types = g_op_tab[op_code - 1].arg_types[*argc];
	if (cur->type != T_WORD)
		error_unexpected_token(cur->len, cur->str, line + 1);
	if ((((arg_types & T_REG) && cur->id == I_REGISTER))
		|| ((arg_types & T_DIR)
		&& (cur->id == I_DIRECT || cur->id == I_DIRECT_LABEL))
		|| ((arg_types & T_IND)
		&& (cur->id == I_INDIRECT || cur->id == I_INDIRECT_LABEL)))
		adat->ops[op_ref].args[*argc] = cur;
	else
	{
		ft_dprintf(2, "parser: wrong argument type '%*.s' at line %d\n",
			cur->len, cur->str, line + 1);
		ft_exit(NULL, E_WRONG_ARGUMENT_TYPE);
	}
	++(*argc);
	return (0);
}

static int	expect_sep(t_token *cur, int line)
{
	if (cur->type != T_SEPARATOR)
	{
		ft_dprintf(2, "parser: missing separator at line %d\n", line + 1);
		ft_exit(NULL, E_MISSING_SEPARATOR);
	}
	return (1);
}

void		parse_instruction(t_asmdata *adat, t_list *tokens,
				int line, int op_ref)
{
	t_token	*cur;
	int		op_code;
	int		sep;

	cur = tokens->content;
	op_code = cur->op_code;
	adat->ops[op_ref].op_code = op_code;
	adat->ops[op_ref].argc = 0;
	sep = 1;
	while (adat->ops[op_ref].argc < g_op_tab[op_code - 1].argc && tokens->next)
	{
		tokens = tokens->next;
		cur = tokens->content;
		if (sep)
			sep = expect_arg(adat, op_ref, cur, line);
		else
			sep = expect_sep(cur, line);
	}
	expect_end(adat, op_ref, tokens, line);
}
