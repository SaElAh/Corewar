/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 00:21:23 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/19 22:26:39 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"
#include "errors.h"

static void		parse_command(t_asmdata *adat, t_list *tokens, int line)
{
	t_token		*command;
	t_token		*value;
	char		*dest;
	int			maxlen;

	value = NULL;
	command = tokens->content;
	if (!(tokens = tokens->next))
	{
		ft_dprintf(2, "parser: command '%.*s' has no argument at line %d\n",
			command->len, command->str, line + 1);
		ft_exit(NULL, E_COMMAND_WITHOUT_ARGUMENT);
	}
	else if ((value = tokens->content)->type != T_STRING)
		error_unexpected_token(value->len, value->str, line + 1);
	dest = !ft_strncmp(NAME_CMD_STRING, command->str, command->len) ?
		adat->prog_name : adat->comment;
	maxlen = dest == adat->prog_name ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	ft_strncpy(dest, value->str + 1, maxlen);
	if (value->len - 2 < maxlen)
		dest[value->len - 2] = 0;
	if (tokens->next)
		error_unexpected_token(((t_token *)tokens->next)->len,
			((t_token *)tokens->next)->str, line + 1);
}

static void		parse_line(t_asmdata *adat, int line, int *op_ref)
{
	t_list	*tokens;
	t_token	*cur;

	tokens = adat->tokens[line];
	cur = tokens->content;
	if (cur->type != T_WORD)
		error_unexpected_token(cur->len, cur->str, line + 1);
	else if (cur->id == I_COMMAND)
		return (parse_command(adat, tokens, line));
	else if (cur->id == I_LABEL)
		while (tokens && (cur = tokens->content)->id == I_LABEL)
		{
			add_label(adat, cur, line, *op_ref + 1);
			tokens = tokens->next;
		}
	cur = tokens ? tokens->content : NULL;
	if (cur && cur->id == I_INSTRUCTION)
		parse_instruction(adat, tokens, line, ++(*op_ref));
	else if (cur)
		error_unexpected_token(cur->len, cur->str, line + 1);
}

static size_t	count_ops(t_list **tokens, size_t file_len)
{
	size_t	i;
	t_list	*ptr;
	t_token	*cur;
	size_t	ops_len;

	i = 0;
	ops_len = 0;
	while (i < file_len)
	{
		ptr = tokens[i++];
		while (ptr)
		{
			cur = (t_token *)ptr->content;
			if (cur->type == T_WORD && cur->id == I_INSTRUCTION)
				++ops_len;
			ptr = ptr->next;
		}
	}
	return (ops_len);
}

void			asm_parser(t_asmdata *adat)
{
	size_t	line;
	int		op_ref;

	if (!(adat->ops_len = count_ops(adat->tokens, adat->file_len)))
		ft_dprintf(2, "warning: parser: no operation in file\n");
	else
		adat->ops = (t_parsed_op *)ft_memalloc(adat->ops_len
			* sizeof(t_parsed_op));
	line = 0;
	op_ref = -1;
	while (line < adat->file_len)
	{
		if (adat->tokens[line])
			parse_line(adat, line, &op_ref);
		++line;
	}
}
