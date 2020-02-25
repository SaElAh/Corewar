/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:45:59 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/25 21:46:01 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"

int		main(int ac, char **av)
{
	t_cor	corewar;
	t_visu	visu;

	corewar = (t_cor){};
	if (init_corewar(&corewar, ac, av))
	{
		free_champs_process(&corewar);
		return (1);
	}
	introduce_champs(&corewar);
	if (corewar.graphic)
	{
		if (ft_visu(&corewar, &visu))
		{
			free_champs_process(&corewar);
			ft_atexit(NULL);
			return (1);
		}
	}
	ft_exec_champs(&corewar, &visu);
	ft_check_winner(&corewar, &visu);
	ft_atexit(NULL);
	return (0);
}
