
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "operations.h"
#include "libft.h"
#include "op.h"

static void		sort_champs_by_id(t_cor *cor)
{
	t_champ		tmp_champ;
	uint32_t	tmp_ind;
	uint32_t	cpt;
	uint32_t	cpt2;

	tmp_ind = 0;
	cpt = -1;
	while (++cpt < cor->nb_champs)
	{
		tmp_ind = cor->champ[cpt].index_champ;
		cpt2 = cpt - 1;
		while (++cpt2 < cor->nb_champs)
		{
			if (cor->champ[cpt2].id_champ < cor->champ[tmp_ind].id_champ)
			{
				tmp_champ = cor->champ[tmp_ind];
				cor->champ[tmp_ind] = cor->champ[cpt2];
				cor->champ[cpt2] = tmp_champ;
				cor->champ[tmp_ind].index_champ = tmp_ind;
				cor->champ[cpt2].index_champ = cpt;
				cpt = 0;
				break ;
			}
		}
	}
}

static int		create_processus(t_cor *cor)
{
	int32_t		i;
	int32_t		ind;
	t_pro		*tmp;

	i = cor->nb_champs;
	ind = 0;
	while (--i >= 0)
	{
		if (!(tmp = ft_memalloc(sizeof(t_pro))))
		{
			free_champs_process(cor);
			return (1);
		}
		tmp->reg[0] = cor->champ[i].id_champ;
		tmp->curr_add = cor->champ[i].curr_add;
		tmp->index_champ = i;
		tmp->index_pro = ++ind;
		tmp->next = cor->tab_process[SIZE_TAB_PRO - 1];
		cor->tab_process[SIZE_TAB_PRO - 1]
			? cor->tab_process[SIZE_TAB_PRO - 1]->prev = tmp : 0;
		cor->tab_process[SIZE_TAB_PRO - 1] = tmp;
	}
	get_curr_char(tmp, cor);
	cor->tab_process[SIZE_TAB_PRO - 1] = NULL;
	return (++cor->curr_ind_process);
}

static void		place_champs(t_cor *cor)
{
	uint32_t	i;
	int			j;
	int32_t		ind;

	ind = cor->nb_champs - 1;
	i = 0;
	j = MEM_SIZE / cor->nb_champs;
	ft_memset(&cor->owner[0], 4, MEM_SIZE);
	while (i < cor->nb_champs)
	{
		cor->champ[ind].index_champ = i;
		cor->champ[ind].curr_add = i * j;
		ft_memcpy(&cor->map[i * j], cor->champ[ind].prog,
				cor->champ[ind].header.prog_size);
		ft_memset(&cor->owner[i * j], ind, cor->champ[ind].header.prog_size);
		i++;
		ind--;
	}
}

static void		init_dispatcher(t_cor *cor)
{
	cor->dispatcher[0] = ft_live;
	cor->dispatcher[1] = ft_ld;
	cor->dispatcher[2] = ft_st;
	cor->dispatcher[3] = ft_add;
	cor->dispatcher[4] = ft_sub;
	cor->dispatcher[5] = ft_and;
	cor->dispatcher[6] = ft_or;
	cor->dispatcher[7] = ft_xor;
	cor->dispatcher[8] = ft_zjmp;
	cor->dispatcher[9] = ft_ldi;
	cor->dispatcher[10] = ft_sti;
	cor->dispatcher[11] = ft_fork;
	cor->dispatcher[12] = ft_lld;
	cor->dispatcher[13] = ft_lldi;
	cor->dispatcher[14] = ft_lfork;
	cor->dispatcher[15] = ft_aff;
}

int				init_corewar(t_cor *cor, int nb_args, char **av)
{
	cor->nb_cycles_dump = UINT_MAX;
	cor->nb_checks = 1;
	cor->curr_ind_process = -1;
	if (parse_arguments(nb_args, av, cor))
	{
		ft_printf("%s: parse_options error\n", *av);
		return (1);
	}
	if (check_champs(cor, av[0]))
		return (1);
	init_dispatcher(cor);
	sort_champs_by_id(cor);
	place_champs(cor);
	if (create_processus(cor))
		return (1);
	cor->biggest_ind_pro = cor->nb_champs;
	return (0);
}
