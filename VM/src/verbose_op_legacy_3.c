/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_op_legacy_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 19:03:56 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/23 17:20:47 by cghanime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"

void	verbose_st(t_cor *cor, t_args args[MAX_ARGS_NUMBER], t_pro *pro,
					int utils[2])
{
	(void)cor;
	ft_printf("P%5i | %s r%i %i\n",
		pro->index_pro, g_op_tab[utils[0]].ope,
		args[0].value, args[1].value);
}
