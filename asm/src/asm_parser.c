/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 00:21:23 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/03 12:45:26 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"
#include "errors.h"

static void		update_command_value(t_token *command, t_token *value,
					t_asmdata *adat)
{
	char		*dest;
	int			maxlen;
	int			name_cmd;

	name_cmd = !ft_strncmp(NAME_CMD_STRING, command->str, command->len);
	dest = name_cmd ? adat->prog_name : adat->comment;
	maxlen = name_cmd ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	if ((name_cmd && adat->name_cmd_count)
		|| (!name_cmd && adat->comment_cmd_count))
		ft_dprintf(2, "warning: parser: multiple '%.*s' commands\n",
			command->len, command->str);
	if (name_cmd)
		adat->name_cmd_count = 1;
	else
		adat->comment_cmd_count = 1;
	ft_strncpy(dest, value->str + 1, maxlen);
	if (value->len - 2 < maxlen)
		dest[value->len - 2] = 0;
	else if (value->len - 2 > maxlen)
		ft_dprintf(2, "warning: parser: the '%.*s' command argument is too\n"\
			"long so it is going to be truncated to %d characters\n",
			command->len, command->str, maxlen);
}

static void		parse_command(t_asmdata *adat, t_list **tokens, int line)
{
	t_token		*command;
	t_token		*value;

	value = NULL;
	command = (*tokens)->content;
	if (!((*tokens) = (*tokens)->next))
		error_command_without_argument(command->len, command->str, line + 1);
	else if ((value = (*tokens)->content)->type != T_STRING)
		error_unexpected_token(value->len, value->str, line + 1);
	update_command_value(command, value, adat);
}
		
#include "debug.h" //TEMP

static void		parse_line(t_asmdata *adat, int line, int *op_ref)
{
	t_list	*tokens;
	t_token	*cur;

	tokens = adat->tokens[line];
	cur = tokens->content;
	if (cur->type != T_WORD)
		error_unexpected_token(cur->len, cur->str, line + 1);
	else if (cur->id != I_INSTRUCTION)
	{
		if (cur->id == I_COMMAND)
			parse_command(adat, &tokens, line);
		else if (cur->id == I_LABEL)
			add_label(adat, cur, line, *op_ref + 1);
		tokens = tokens->next;
		cur = tokens ? tokens->content : NULL;
	}
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
	if (!adat->name_cmd_count)
		ft_exit("error: no name command in file", E_NO_NAME);
	else if (!adat->comment_cmd_count)
		ft_exit("error: no comment command in file", E_NO_COMMENT);
}
