/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_curr_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:45:43 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/25 21:45:44 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static t_pro	*init_get_curr_char(t_pro *pro, t_cor *cor, int64_t *dest)
{
	pro->curr_char = cor->map[pro->curr_add];
	if (pro->curr_char > 0 && pro->curr_char < 17)
		*dest = (cor->curr_ind_process
			+ g_op_tab[pro->curr_char - 1].nb_cycles) % SIZE_TAB_PRO;
	else
		*dest = (cor->curr_ind_process + 1) % SIZE_TAB_PRO;
	return (cor->tab_process[*dest]);
}

static void		insert_pro(t_pro *tmp2, t_pro *pro)
{
	t_pro	*tmp1;

	tmp1 = tmp2->next;
	while (tmp1 && tmp1->index_pro > pro->index_pro)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
	}
	tmp2->next = pro;
	pro->next = tmp1;
	tmp1 ? tmp1->prev = pro : 0;
	pro->prev = tmp2;
}

void			get_curr_char(t_pro *pro, t_cor *cor)
{
	t_pro	*nxt;
	t_pro	*tmp2;
	int64_t	dest;

	while (pro)
	{
		nxt = pro->next;
		tmp2 = init_get_curr_char(pro, cor, &dest);
		if (!tmp2 || tmp2->index_pro < pro->index_pro)
		{
			pro->next = tmp2;
			pro->prev = NULL;
			tmp2 ? tmp2->prev = pro : 0;
			cor->tab_process[dest] = pro;
		}
		else
			insert_pro(tmp2, pro);
		pro = nxt;
	}
}
