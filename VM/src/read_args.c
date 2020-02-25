/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 22:59:18 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/23 18:08:59 by cghanime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static int	read_ocp(int op, t_args args[MAX_ARGS_NUMBER],
				t_cor *cor, t_pro *pro)
{
	uint8_t	ocp;
	int		err;
	int		i;

	ocp = cor->map[pro->curr_add++];
	adjust_curr_add(&pro->curr_add);
	i = -1;
	err = 0;
	while (++i < g_op_tab[op].nb_args)
		if (!(args[i].type = (ocp >> ((3 - i) * 2)) & 0x03)
			|| (args[i].type == REG_CODE
			&& !(g_op_tab[op].type_args[i] & T_REG))
			|| (args[i].type == DIR_CODE
			&& !(g_op_tab[op].type_args[i] & T_DIR))
			|| (args[i].type == IND_CODE
			&& !(g_op_tab[op].type_args[i] & T_IND)))
			err = 1;
	return (err);
}

static int	get_args_types(int op, t_args args[MAX_ARGS_NUMBER],
								t_cor *cor, t_pro *pro)
{
	int	err;
	int	i;

	i = -1;
	err = 0;
	if (g_op_tab[op].ocp)
		err = read_ocp(op, args, cor, pro);
	else
		while (++i < g_op_tab[op].nb_args)
			args[i].type = g_op_tab[op].type_args[i] == T_IND ?
				IND_CODE : g_op_tab[op].type_args[i];
	i = -1;
	while (++i < g_op_tab[op].nb_args)
	{
		args[i].size = 0;
		if (args[i].type == REG_CODE)
			args[i].size = 1;
		else if (args[i].type == IND_CODE)
			args[i].size = 2;
		else if (args[i].type == DIR_CODE)
			args[i].size = g_op_tab[op].dir_size;
	}
	return (err);
}

static void	get_value(uint8_t map[MEM_SIZE], int64_t *curr_add,
						t_args *args)
{
	int		j;
	uint8_t	*val;

	j = 0;
	val = (uint8_t *)&args->value;
	while (j < args->size)
	{
		val[args->size - 1 - j] = map[(*curr_add)++];
		adjust_curr_add(curr_add);
		j++;
	}
}

int			read_args(t_args args[MAX_ARGS_NUMBER], t_cor *cor, t_pro *pro)
{
	int		i;
	int		op;
	int		err;

	op = pro->curr_char - 1;
	pro->curr_add++;
	adjust_curr_add(&pro->curr_add);
	err = get_args_types(op, args, cor, pro);
	i = -1;
	while (++i < g_op_tab[op].nb_args)
	{
		args[i].value = args[i].size == 2 && cor->map[pro->curr_add] & 128 ?
			-1 : 0;
		get_value(cor->map, &pro->curr_add, &args[i]);
		if (args[i].type == REG_CODE)
			err |= (args[i].value < 1 || args[i].value > 16);
	}
	return (err);
}
