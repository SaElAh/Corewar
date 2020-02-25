/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:39:11 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/23 18:33:00 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		ft_zjmp(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];
	int		curr_add;

	curr_add = pro->curr_add;
	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){8, curr_add});
	if (pro->carry)
		pro->curr_add = curr_add + args[0].value;
	adjust_curr_add(&pro->curr_add);
	return (0);
}
