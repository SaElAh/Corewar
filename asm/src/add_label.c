/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 21:08:53 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/18 00:22:30 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_parser.h"
#include "errors.h"

static int	label_cmp(void *l1, void *l2)
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
	t_list	*lst;

	label.name = cur->str;
	label.name_len = cur->len - 1;
	label.op_ref = op_ref;
	label.line = line;
	lst = ft_lstnew((void *)&label, sizeof(t_label));
	ft_lst_sorted_insert(&adat->labels, lst, label_cmp);
	if (lst->next && !label_cmp(lst->content, lst->next->content))
	{
		ft_dprintf(2, "parser: label '%.*s' declared \
			twice (at line %d and %d)\n", label.name_len, label.name,
			((t_label *)lst->next->content)->line, line);
		ft_exit(NULL, E_LABEL_DECLARED_TWICE);
	}
}
