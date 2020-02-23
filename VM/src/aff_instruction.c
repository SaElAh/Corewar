/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:41:51 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/02 16:50:30 by cghanime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int		ft_aff(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];
	char	c;

	if (read_args(args, cor, pro))
		return (1);
	print_args(cor, args, g_op_tab[15].nb_args, pro->carry);
	c = (char)pro->reg[args[0].value - 1];
	return (0);
}
