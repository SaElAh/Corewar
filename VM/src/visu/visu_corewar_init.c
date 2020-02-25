/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_corewar_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 17:05:23 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/25 21:48:19 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"

void			init_colors(void)
{
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_RED, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

static void		init_visu(t_visu *visu)
{
	size_t	i;

	i = 0;
	ft_memset(visu, 0, sizeof(t_visu));
	while (i < MEMORY)
	{
		visu->owner[i].owner = EMPTY;
		i++;
	}
}

void			get_info(t_visu *visu, t_cor *cor)
{
	WINDOW * vm;
	WINDOW * dash;
	if (!(vm = subwin(stdscr, LINES, 272, 0, 0)))
		ft_exit("subwin: failed to create vm sub window", EXIT_FAILURE);
	ft_heap_collector((void *)vm, FT_COLLEC_ADD);
	if (!(dash = subwin(stdscr, LINES, 91, 0, 272)))
		ft_exit("subwin: failed to create dash sub window", EXIT_FAILURE);
	ft_heap_collector((void *)dash, FT_COLLEC_ADD);
	init_visu(visu);
	visu->cor = cor;
	visu->vm = vm;
	visu->dash = dash;
}
