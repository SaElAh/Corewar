/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_op_legacy_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 19:02:48 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/23 17:20:47 by cghanime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"

void	verbose_add_sub(t_cor *cor, t_args args[MAX_ARGS_NUMBER], t_pro *pro,
						int utils[2])
{
	(void)cor;
	ft_printf("P%5i | %s r%i r%i r%i\n",
		pro->index_pro, g_op_tab[utils[0]].ope,
		utils[0] == 3 || utils[0] == 4 ? args[0].value : args[0].value - 1,
		utils[0] == 3 || utils[0] == 4 ? args[1].value : args[1].value - 1,
		args[2].type == REG_CODE ? args[2].value : args[2].value - 1);
}

void	verbose_and_or_xor(t_cor *cor, t_args args[MAX_ARGS_NUMBER], t_pro *pro,
					int utils[2])
{
	(void)cor;
	ft_printf("P%5i | %s %i %i r%i\n",
		pro->index_pro, g_op_tab[utils[0]].ope,
		args[0].type == REG_CODE ? pro->reg[args[0].value - 1] : args[0].value,
		args[1].type == REG_CODE ? pro->reg[args[1].value - 1] : args[1].value,
		args[2].value);
}

void	verbose_forks(t_cor *cor, t_args args[MAX_ARGS_NUMBER], t_pro *pro,
					int utils[2])
{
	(void)cor;
	ft_printf("P%5i | %s %i (%lli)\n",
		pro->index_pro, g_op_tab[utils[0]].ope,
		args[0].value, utils[0] == 11 ?
		pro->curr_add - 3 + args[0].value % IDX_MOD
		: pro->curr_add - 3 + args[0].value);
}

void	verbose_live_zjmp(t_cor *cor, t_args args[MAX_ARGS_NUMBER], t_pro *pro,
					int utils[2])
{
	(void)cor;
	if (utils[0] == 8)
	{
		ft_printf("P%5i | %s %i%s\n",
			pro->index_pro, g_op_tab[utils[0]].ope,
			args[0].value, pro->carry == 1 ? " OK" : " FAILED");
	}
	else
	{
		ft_printf("P%5i | %s %i\n",
			pro->index_pro, g_op_tab[utils[0]].ope,
			args[0].value);
	}
}

void	verbose_ld(t_cor *cor, t_args args[MAX_ARGS_NUMBER], t_pro *pro,
					int utils[2])
{
	int64_t	curr_addtmp;
	int		tmp1;

	(void)cor;
	curr_addtmp = utils[1] + (args[0].value) % IDX_MOD;
	adjust_curr_add(&curr_addtmp);
	tmp1 = read_map(cor->map, curr_addtmp);
	ft_printf("P%5i | %s %i r%i\n",
		pro->index_pro, g_op_tab[utils[0]].ope,
		args[0].type == IND_CODE ? tmp1 : args[0].value,
		args[1].value);
}
