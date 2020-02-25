/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:42:53 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/23 18:29:35 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"

int		ft_live(t_cor *cor, t_pro *pro)
{
	uint8_t		i;
	t_args		args[MAX_ARGS_NUMBER];

	i = 0;
	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){0, 0});
	pro->nb_lives += 1;
	pro->last_cycle_live = cor->nb_cycles;
	while (i < cor->nb_champs)
	{
		if (args[0].value == (int)cor->champ[i].id_champ)
		{
			if (cor->verbose & VERBOSE_LIVES)
				ft_printf("Player %i (%s) is said to be alive\n",
				cor->nb_champs - i, cor->champ[i].header.prog_name);
			cor->champ[i].nb_lives += 1;
			cor->champ[i].last_cycle_live = cor->nb_cycles;
			return (0);
		}
		i++;
	}
	return (0);
}
