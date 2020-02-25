/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_live_fct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:46:13 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/25 21:46:15 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"

void			ft_free_process_node(t_pro **process)
{
	t_pro	*tmp;

	(*process)->prev ? (*process)->prev->next = (*process)->next : 0;
	(*process)->next ? (*process)->next->prev = (*process)->prev : 0;
	tmp = (*process)->next;
	ft_memdel((void **)process);
	(*process) = tmp;
}

uint32_t		sum_lives(t_cor *cor, int ind)
{
	uint32_t	cpt_tot;
	t_pro		*tmp;

	cpt_tot = 0;
	tmp = cor->tab_process[ind];
	while (tmp)
	{
		cpt_tot += tmp->nb_lives;
		if (!tmp->nb_lives)
		{
			if (cor->verbose & VERBOSE_DEATH)
				ft_printf("Process %i hasn't lived for %i cycles (CTD %i)\n",
tmp->index_pro, cor->nb_cycles - tmp->last_cycle_live, cor->cycles_to_die_ref);
			if (cor->tab_process[ind] == tmp)
			{
				ft_free_process_node(&tmp);
				cor->tab_process[ind] = tmp;
			}
			else
				ft_free_process_node(&tmp);
			continue ;
		}
		tmp = tmp->next;
	}
	return (cpt_tot);
}

void			re_init_lives_champs(t_cor *cor)
{
	int			i;
	t_pro		*tmp;

	i = 0;
	while (i < SIZE_TAB_PRO)
	{
		tmp = cor->tab_process[i];
		while (tmp)
		{
			tmp->nb_lives = 0;
			tmp = tmp->next;
		}
		i++;
	}
}

int				ft_check_lives(t_cor *cor)
{
	int i;
	int	cpt;

	cpt = 0;
	cor->sum_lives = 0;
	i = cor->curr_ind_process;
	while (cpt < SIZE_TAB_PRO)
	{
		cor->sum_lives += sum_lives(cor, i);
		i = (i + 1) % SIZE_TAB_PRO;
		cpt++;
	}
	if (!cor->sum_lives)
		return (1);
	else
	{
		if (cor->sum_lives >= NBR_LIVE || cor->nb_checks >= MAX_CHECKS)
			re_init_check_utils(cor, 2);
		else
			re_init_check_utils(cor, 1);
	}
	return (0);
}
