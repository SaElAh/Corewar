/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_op_legacy_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 19:03:56 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/02 19:04:14 by cghanime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include <stdio.h>

void	verbose_st(t_cor *cor, t_args args[MAX_ARGS_NUMBER], t_pro *pro,
					int utils[2])
{
	(void)cor;
	printf("P%5i | %s r%i %i\n",
		pro->index_pro, g_op_tab[utils[0]].ope,
		args[0].value, args[1].value);
}
