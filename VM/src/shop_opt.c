/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shop_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:46:30 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/25 21:46:34 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "op.h"

void	show_opt(t_cor *cor, int kase)
{
	int		c;

	c = 0;
	if (kase == 0 && cor->show_opt)
	{
		print_map(cor);
		read(0, &c, 1);
	}
	else if (kase == 1
				&& cor->show_opt && !(cor->nb_cycles % cor->show_opt))
	{
		print_map(cor);
		read(0, &c, 1);
	}
}
