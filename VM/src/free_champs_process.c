/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_champs_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:45:40 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/25 21:45:41 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"

void			free_champs_process(t_cor *cor)
{
	t_pro	*tmp;
	t_pro	*tmp2;
	int		i;

	i = 0;
	while (i < SIZE_TAB_PRO)
	{
		tmp = cor->tab_process[i];
		while (tmp)
		{
			tmp2 = tmp->next;
			ft_memdel((void **)&tmp);
			tmp = tmp2;
		}
		i++;
	}
}
