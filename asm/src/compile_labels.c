/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_labels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:06:50 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/19 18:43:45 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"
#include "errors.h"

static void	write_label_bytes(t_asmdata *adat, unsigned int dest,
				int value, unsigned int size)
{
	unsigned char	*bin;

	bin = (unsigned char *)&value;
	while (size)
		adat->prog[dest++] = bin[--size];
}

static void	replace_label_value(t_asmdata *adat, size_t i, size_t j)
{
	int		value;
	t_label	cur;
	size_t	offset;
	t_list	*match;
	t_label	*matched_label;

	offset = adat->ops[i].args[j]->id == I_DIRECT_LABEL ? 2 : 1;
	cur.name = adat->ops[i].args[j]->str + offset;
	cur.name_len = adat->ops[i].args[j]->len - offset;
	if (!(match = ft_lst_find(adat->labels, &cur, label_cmp)))
	{
		ft_dprintf(2, "compiler: no match found for label '%.*s'\n",
			cur.name_len, cur.name);
		ft_exit(NULL, E_NO_LABEL_MATCH);
	}
	matched_label = match->content;
	if (matched_label->op_ref < (int)adat->ops_len)
		value =	adat->ops[matched_label->op_ref].address - adat->ops[i].address;
	else
		value = adat->prog_size - adat->ops[i].address;
	write_label_bytes(adat, adat->ops[i].address + adat->ops[i].label_add[j],
		value, adat->ops[i].args[j]->id == I_INDIRECT_LABEL 
		|| g_op_tab[adat->ops[i].op_code - 1].mod_tdir_size ? IND_BYTE_SIZE
		: DIR_BYTE_SIZE);
}

void		compile_labels(t_asmdata *adat)
{
	size_t			i;
	size_t			j;

	i = 0;
	while (i < adat->ops_len)
	{
		j = 0;
		while (j < adat->ops[i].argc)
		{
			if (adat->ops[i].label_add[j])
				replace_label_value(adat, i, j);
			++j;
		}
		++i;
	}
}
