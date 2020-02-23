/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:41:51 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/23 18:25:59 by yforeau          ###   ########.fr       */
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
	c = (char)pro->reg[args[0].value - 1];
	return (0);
}
