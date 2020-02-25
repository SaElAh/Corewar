/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_instructions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:46:06 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/25 21:46:07 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		ft_add(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];

	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){3, 0});
	pro->reg[args[2].value - 1] = pro->reg[args[0].value - 1]
		+ pro->reg[args[1].value - 1];
	pro->carry = !pro->reg[args[2].value - 1];
	return (0);
}

int		ft_sub(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];

	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){4, 0});
	pro->reg[args[2].value - 1] = pro->reg[args[0].value - 1]
		- pro->reg[args[1].value - 1];
	pro->carry = !pro->reg[args[2].value - 1];
	return (0);
}

int		ft_and(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];
	int		val[2];
	int		i;
	int		curr_add;

	curr_add = pro->curr_add;
	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){5, curr_add});
	i = -1;
	while (++i < 2)
	{
		if (args[i].type == REG_CODE)
			val[i] = pro->reg[args[i].value - 1];
		else if (args[i].type == DIR_CODE)
			val[i] = args[i].value;
		else
			val[i] = read_map(cor->map, curr_add + (args[i].value % IDX_MOD));
	}
	pro->reg[args[2].value - 1] = val[0] & val[1];
	pro->carry = !pro->reg[args[2].value - 1];
	return (0);
}

int		ft_or(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];
	int		val[2];
	int		i;
	int		curr_add;

	curr_add = pro->curr_add;
	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){6, curr_add});
	i = -1;
	while (++i < 2)
	{
		if (args[i].type == REG_CODE)
			val[i] = pro->reg[args[i].value - 1];
		else if (args[i].type == DIR_CODE)
			val[i] = args[i].value;
		else
			val[i] = read_map(cor->map, curr_add + (args[i].value % IDX_MOD));
	}
	pro->reg[args[2].value - 1] = val[0] | val[1];
	pro->carry = !pro->reg[args[2].value - 1];
	return (0);
}

int		ft_xor(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];
	int		val[2];
	int		i;
	int		curr_add;

	curr_add = pro->curr_add;
	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){7, curr_add});
	i = -1;
	while (++i < 2)
	{
		if (args[i].type == REG_CODE)
			val[i] = pro->reg[args[i].value - 1];
		else if (args[i].type == DIR_CODE)
			val[i] = args[i].value;
		else
			val[i] = read_map(cor->map, curr_add + (args[i].value % IDX_MOD));
	}
	pro->reg[args[2].value - 1] = val[0] ^ val[1];
	pro->carry = !pro->reg[args[2].value - 1];
	return (0);
}
