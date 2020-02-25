
#include "libft.h"
#include "op.h"
#include "operations.h"

void				re_init_check_utils(t_cor *cor, int kase)
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
			ft_printf("Cycle to die is now %i\n", cor->cycles_to_die_ref);
		cor->cycles_to_die = cor->cycles_to_die_ref;
	}
	kase == 2 || !kase ? cor->nb_checks = 1 : 0;
	kase ? re_init_lives_champs(cor) : 0;
	kase == 1 ? (cor->nb_checks += 1) : 0;
}

extern inline void	adjust_curr_add(int64_t *address)
{
	if (*address >= MEM_SIZE)
		*address %= MEM_SIZE;
	if (*address < 0)
		*address = *address % MEM_SIZE + MEM_SIZE;
}

static void			call_instruction(t_cor *cor, t_pro *pro, int64_t prev_add)
{
	int64_t	tmp_add;

	if (cor->dispatcher[pro->curr_char - 1](cor, pro)
			&& cor->verbose & VERBOSE_OP_LEGACY)
	{
		tmp_add = prev_add + 1;
		adjust_curr_add(&tmp_add);
		ft_printf("ADV 2 (0x%04llx -> 0x%04llx) %02x %02x \n",
			prev_add, pro->curr_add, cor->map[prev_add], cor->map[tmp_add]);
	}
	verbose_pc(pro, cor, prev_add);
}

static void			ft_exec_process(t_cor *cor)
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

void				ft_exec_champs(t_cor *cor, t_visu *visu)
{
	re_init_check_utils(cor, 0);
	show_opt(cor, 0);
	while (cor->nb_cycles < cor->nb_cycles_dump &&
				cor->cycles_to_die_ref - CYCLE_DELTA > -50)
	{
		++cor->nb_cycles;
		--cor->cycles_to_die;
		if (cor->verbose & VERBOSE_CYCLES)
			ft_printf("It is now cycle %i\n", cor->nb_cycles);
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
