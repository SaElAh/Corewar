/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_op_legacy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 19:02:03 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/02 19:04:16 by cghanime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include <stdio.h>

t_pf_verbose	g_pf_verbose =
{
	&verbose_live_zjmp,
	&verbose_ld,
	&verbose_st,
	&verbose_add_sub,
	&verbose_add_sub,
	&verbose_and_or_xor,
	&verbose_and_or_xor,
	&verbose_and_or_xor,
	&verbose_live_zjmp,
	&verbose_ldi,
	&verbose_sti,
	&verbose_forks,
	&verbose_lld,
	&verbose_lldi,
	&verbose_forks,
};

void	print_op(t_cor *cor, t_args args[MAX_ARGS_NUMBER], t_pro *pro,
					int utils[2])
{
	if (!(cor->verbose & VERBOSE_OP_LEGACY))
		return ;
	g_pf_verbose[utils[0]](cor, args, pro, utils);
}

void	verbose_sti(t_cor *cor, t_args args[MAX_ARGS_NUMBER], t_pro *pro,
					int utils[2])
{
	int		tmp1;
	int		tmp2;
	int64_t	curr_addtmp;

	if (args[1].type == IND_CODE)
		tmp1 = read_map(cor->map, utils[1] + (args[1].value % IDX_MOD));
	else
		tmp1 = args[1].type == REG_CODE
		? pro->reg[args[1].value - 1] : args[1].value;
	tmp2 = args[2].type == REG_CODE ? pro->reg[args[2].value - 1]
										: args[2].value;
	curr_addtmp = args[1].type == DIR_CODE ? utils[1] + (tmp1 + tmp2) % IDX_MOD
										: (utils[1] + tmp1 + tmp2);
	adjust_curr_add(&curr_addtmp);
	printf("P%5i | %s r%i %i %i\n",
		pro->index_pro, g_op_tab[utils[0]].ope,
		args[0].value, tmp1, tmp2);
	printf("       | -> %s to %i + %i = %i (with pc and mod %lli)\n",
			g_op_tab[utils[0]].description, tmp1, tmp2,
			tmp1 + tmp2, curr_addtmp);
}

void	verbose_ldi(t_cor *cor, t_args args[MAX_ARGS_NUMBER], t_pro *pro,
					int utils[2])
{
	int		tmp1;
	int		tmp2;
	int64_t	curr_addtmp;

	if (args[0].type == IND_CODE)
		tmp1 = read_map(cor->map, utils[1] + args[1].value % IDX_MOD);
	else
		tmp1 = args[0].type == REG_CODE ? pro->reg[args[0].value - 1]
										: args[0].value;
	tmp2 = args[1].type == REG_CODE ? pro->reg[args[1].value - 1]
									: args[1].value;
	curr_addtmp = (utils[1] + tmp1 + tmp2) % IDX_MOD;
	adjust_curr_add(&curr_addtmp);
	printf("P%5i | %s %i %i r%i\n",
		pro->index_pro, g_op_tab[utils[0]].ope, tmp1, tmp2,
		args[2].value);
	printf("       | -> load from %i + %i = %i (with pc and mod %lli)\n",
			tmp1, tmp2, tmp1 + tmp2, curr_addtmp);
}

void	verbose_lld(t_cor *cor, t_args args[MAX_ARGS_NUMBER], t_pro *pro,
					int utils[2])
{
	int64_t		curr_addtmp;
	int			tmp1;
	uint8_t		*lul;

	curr_addtmp = utils[1] + args[0].value;
	adjust_curr_add(&curr_addtmp);
	tmp1 = read_map(cor->map, curr_addtmp);
	lul = (uint8_t*)&tmp1;
	lul[0] = lul[2];
	lul[1] = lul[3];
	lul[3] = 0;
	lul[2] = 0;
	printf("P%5i | %s %i r%i\n",
		pro->index_pro, g_op_tab[utils[0]].ope,
		args[0].type == IND_CODE ? tmp1
		: args[0].value, args[1].value);
}

void	verbose_lldi(t_cor *cor, t_args args[MAX_ARGS_NUMBER], t_pro *pro,
						int utils[2])
{
	int		tmp1;
	int		tmp2;
	int64_t	curr_addtmp;

	if (args[0].type == REG_CODE)
		tmp1 = pro->reg[args[0].value - 1];
	else
		tmp1 = args[0].type == IND_CODE
			? read_map(cor->map, (utils[1] + args[0].value))
			: args[0].value;
	if (args[1].type == REG_CODE)
		tmp2 = pro->reg[args[1].value - 1];
	else
		tmp2 = args[1].type == IND_CODE
				? read_map(cor->map, (utils[1] + args[1].value))
				: args[1].value;
	curr_addtmp = (utils[1] + tmp1 + tmp2);
	printf("P%5i | %s %i %i r%i\n",
		pro->index_pro, g_op_tab[utils[0]].ope,
		tmp1, tmp2, args[2].value);
	printf("       | -> load from %i + %i = %i (with pc %lli)\n",
			tmp1, tmp2, tmp1 + tmp2, curr_addtmp);
}
