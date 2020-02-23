/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:39:11 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/02 16:48:08 by cghanime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int		ft_zjmp(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];
	int		curr_add;

	curr_add = pro->curr_add;
	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){8, curr_add});
	print_args(cor, args, g_op_tab[8].nb_args, pro->carry);
	if (pro->carry)
		pro->curr_add = curr_add + args[0].value;
	adjust_curr_add(&pro->curr_add);
	return (0);
}
