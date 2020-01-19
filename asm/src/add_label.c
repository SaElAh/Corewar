/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 21:08:53 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/19 19:06:03 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"
#include "errors.h"

int		label_cmp(void *l1, void *l2)
{
	t_label	*label1;
	t_label	*label2;
	size_t	len;
	int		ret;

	label1 = l1;
	label2 = l2;
	len = label1->name_len < label2->name_len ?
		label1->name_len : label2->name_len;
	ret = ft_strncmp(label1->name, label2->name, len);
	return (!ret ? label1->name_len - label2->name_len : ret);
}

void		add_label(t_asmdata *adat, t_token *cur, int line, int op_ref)
{
	t_label	label;

	label.name = cur->str;
	label.name_len = cur->len - 1;
	label.op_ref = op_ref;
	label.line = line;
	ft_lst_push_back(&adat->labels, &label, sizeof(t_label));
}
