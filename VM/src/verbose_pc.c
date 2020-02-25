/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_pc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:46:51 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/25 21:46:52 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"

void			verbose_pc(t_pro *tmp, t_cor *cor, int64_t tmp_add)
{
	int	i;

	if (cor->verbose & VERBOSE_PC && (tmp->curr_char != 9
			|| (tmp->curr_char == 9 && !tmp->carry)))
	{
		if (tmp->curr_add - tmp_add == 2)
			return ;
		ft_printf("ADV %lli (0x%.4llx -> 0x%.4llx) ",
				tmp->curr_add - tmp_add, tmp_add, tmp->curr_add);
		i = 0;
		while (i < tmp->curr_add - tmp_add)
		{
			ft_printf("%.2x ", cor->map[i + tmp_add]);
			i++;
		}
		ft_printf("\n");
	}
}
