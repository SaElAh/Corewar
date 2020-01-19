/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 23:16:25 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/19 23:24:34 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"

const char		*g_token_type_str[TOKEN_TYPE_COUNT] = {
	"T_WORD", "T_STRING", "T_START_STRING", "T_PART_STRING", "T_END_STRING",
	"T_SEPARATOR", "T_NONE"
};

const char		*g_token_word_id[TOKEN_ID_COUNT] = {
	"I_COMMAND", "I_LABEL", "I_INSTRUCTION", "I_REGISTER", "I_DIRECT",
	"I_INDIRECT", "I_DIRECT_LABEL", "I_INDIRECT_LABEL", "I_NONE"
};

void			print_file(t_list *file)
{
	int		lc;

	lc = 0;
	while (file)
	{
		ft_printf("%d: '%s'\n", ++lc, (char *)file->content);
		file = file->next;
	}
}

void			print_tokens(t_list **tokens, int len)
{
	int		i;
	t_token	*cur;
	t_list	*line;

	i = -1;
	while (++i < len)
	{
		if ((line = tokens[i]))
			ft_printf("line %d:\n", i + 1);
		while (line)
		{
			cur = (t_token *)line->content;
			ft_printf("[ type = %s, id = %s, op_code = %d, str = %.*s ]\n",
				g_token_type_str[cur->type], g_token_word_id[cur->id],
				cur->op_code, cur->len, cur->str);
			line = line->next;
		}
	}
}

void			print_ops(t_parsed_op *ops, size_t ops_len)
{
	size_t			i;
	unsigned int	j;
	t_token			*cur;

	i = 0;
	while (i < ops_len)
	{
		ft_printf("ops[%zu]: %s, argc = %u\nargs:\n", i,
			g_op_tab[ops[i].op_code - 1].name, ops[i].argc);
		j = 0;
		while (j < ops[i].argc)
		{
			cur = ops[i].args[j++];
			ft_printf("[ type = %s, id = %s, op_code = %d, str = %.*s ]\n",
				g_token_type_str[cur->type], g_token_word_id[cur->id],
				cur->op_code, cur->len, cur->str);
		}
		++i;
	}
}

void			print_labels(t_list *labels)
{
	t_label	*cur;

	while (labels)
	{
		cur = labels->content;
		ft_printf("label '%.*s': op_ref = %d, line = %d\n", cur->name_len,
			cur->name, cur->op_ref, cur->line);
		labels = labels->next;
	}
}

void			print_hex_prog(t_asmdata *adat)
{
	unsigned int	address;
	unsigned int	i;

	address = 0;
	while (address < adat->prog_size)
	{
		ft_printf("%.8x:", address);
		i = 0;
		while (address + i < adat->prog_size && i < 16)
		{
			if (!(i % 2))
				ft_printf(" ");
			ft_printf("%.2x", adat->prog[address + i]);
			++i;
		}
		ft_printf("\n");
		address += 16;
	}
}
