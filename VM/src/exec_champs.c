
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "op.h"
#include "operations.h"

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
			free(tmp);
			tmp = tmp2;
		}
		i++;
	}
}

void	ft_check_winner(t_cor *cor)
{
	uint32_t	i;
	uint32_t	winner;
	uint32_t	last_cycle;
	uint32_t	ind_winner;

	i = 0;
	last_cycle = cor->champ[i].last_cycle_live;
	winner = cor->champ[i].index_champ;
	ind_winner = i;
	while (i < cor->nb_champs)
	{
		if (cor->champ[i].last_cycle_live >= last_cycle)
		{
			last_cycle = cor->champ[i].last_cycle_live;
			winner = cor->champ[i].index_champ;
			ind_winner = i;
		}
		i++;
	}
	printf("Contestant %d, \"%s\", has won !\n",
		cor->nb_champs - ind_winner,
		cor->champ[ind_winner].header.prog_name);
	free_champs_process(cor);
}

void			re_init_check_utils(t_cor *cor, int kase)
{
	if (!kase)
	{
		cor->cycles_to_die_ref = CYCLE_TO_DIE;
		cor->cycles_to_die = CYCLE_TO_DIE;
	}
	else
	{
		cor->cycles_to_die_ref -= kase == 2 ? CYCLE_DELTA : 0;
		if (kase == 2 && (cor->verbose & VERBOSE_CYCLES))
			printf("Cycle to die is now %i\n", cor->cycles_to_die_ref);
		cor->cycles_to_die = cor->cycles_to_die_ref;
	}
	kase == 2 || !kase ? cor->nb_checks = 1 : 0;
	kase ? re_init_lives_champs(cor) : 0;
	kase == 1 ? (cor->nb_checks += 1) : 0;
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

extern inline void	adjust_curr_add(int64_t *address)
{
	if (*address >= MEM_SIZE)
		*address %= MEM_SIZE;
	if (*address < 0)
		*address = *address % MEM_SIZE + MEM_SIZE;
}

t_pro	*init_get_curr_char(t_pro *pro, t_cor *cor, int64_t	*dest)
{
	pro->curr_char = cor->map[pro->curr_add];
	if (pro->curr_char > 0 && pro->curr_char < 17)
		*dest = (cor->curr_ind_process
			+ g_op_tab[pro->curr_char - 1].nb_cycles) % SIZE_TAB_PRO;
	else
		*dest = (cor->curr_ind_process + 1) % SIZE_TAB_PRO;
	return (cor->tab_process[*dest]);
}

void	insert_pro(t_pro *tmp2, t_pro *pro)
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

void	get_curr_char(t_pro *pro, t_cor *cor)
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


void	call_instruction(t_cor *cor, t_pro *pro, int64_t prev_add)
{
	int64_t	tmp_add;

	if (cor->dispatcher[pro->curr_char - 1](cor, pro)
			&& cor->verbose & VERBOSE_OP_LEGACY)
	{
		tmp_add = prev_add + 1;
		adjust_curr_add(&tmp_add);
		printf("ADV 2 (0x%04llx -> 0x%04llx) %02x %02x \n",
			prev_add, pro->curr_add, cor->map[prev_add], cor->map[tmp_add]);
	}
	verbose_pc(pro, cor, prev_add);
}

void	ft_exec_process(t_cor *cor)
{
	t_pro			*tmp;
	int64_t			prev_add;

	tmp = cor->tab_process[cor->curr_ind_process];
	while (tmp)
	{
		if (!tmp->curr_char || tmp->curr_char > 16)
		{
			tmp->curr_add += 1;
			adjust_curr_add(&tmp->curr_add);
		}
		else
		{
			prev_add = tmp->curr_add;
			call_instruction(cor, tmp, prev_add);
		}
		tmp = tmp->next;
	}
	get_curr_char(cor->tab_process[cor->curr_ind_process], cor);
	cor->tab_process[cor->curr_ind_process] = NULL;
}

void	show_opt(t_cor *cor, int kase)
{
	int		c;

	c = 0;
	if (kase == 0 && cor->show_opt)
	{
		print_map(cor);
		read(0, &c, 1);
	}
	else if (kase == 1
				&& cor->show_opt && !(cor->nb_cycles % cor->show_opt))
	{
		print_map(cor);
		read(0, &c, 1);
	}
}

void	ft_exec_champs(t_cor *cor, t_visu *visu)
{
	re_init_check_utils(cor, 0);
	show_opt(cor, 0);
	while (cor->nb_cycles < cor->nb_cycles_dump &&
				cor->cycles_to_die_ref - CYCLE_DELTA > -50)
	{
		++cor->nb_cycles;
		--cor->cycles_to_die;
		if (cor->verbose & VERBOSE_CYCLES)
			printf("It is now cycle %i\n", cor->nb_cycles);
		ft_exec_process(cor);
		if (!cor->cycles_to_die)
		{
			if (ft_check_lives(cor))
				break ;
		}
		cor->curr_ind_process = (cor->curr_ind_process + 1) % SIZE_TAB_PRO;
		show_opt(cor, 1);
		if (cor->graphic)
			call_map_check_process(visu);
	}
//	++cor->nb_cycles;
//	--cor->cycles_to_die;
//	ft_exec_process(cor);
//	ft_check_lives(cor);

	if (cor->dump_opt && cor->nb_cycles == cor->nb_cycles_dump)
		print_map(cor);
	ft_check_winner(cor);
}
