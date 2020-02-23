/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_corewar_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:29:51 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/23 16:41:29 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	maj_map_owner(t_visu *visu)
{
	int i;

	i = 0;
	while (i < MEMORY)
	{
		visu->owner[i].owner = visu->cor->owner[i];
		i++;
	}
}

void	call_map_check_process(t_visu *visu)
{
	t_pro	*pro;
	int		i;

	i = 0;
	maj_map_owner(visu);
	nprint_map(visu, MEMORY);
	mvwprintw(visu->dash, 50, 1, "nb_cycles = %d ", visu->cor->nb_cycles);
	while (i < SIZE_TAB_PRO)
	{
		pro = visu->cor->tab_process[i++];
		while (pro)
		{
			if (pro->index_champ == 0)
				print_champ_area(visu, pro->curr_add);
			else if (pro->index_champ == 1)
				print_champ_area(visu, pro->curr_add);
			else if (pro->index_champ == 2)
				print_champ_area(visu, pro->curr_add);
			else if (pro->index_champ == 3)
				print_champ_area(visu, pro->curr_add);
			pro = pro->next;
			wrefresh(visu->vm);
			wrefresh(visu->dash);
		}
	}
}

void	init_nprint_map(size_t *row, size_t *col, size_t *i, size_t *j)
{
	*row = 1;
	*col = 0;
	*i = 0;
	*j = 0;
}

void	nprint_map(t_visu *visu, size_t len)
{
	size_t	row;
	size_t	col;
	size_t	i;
	size_t	j;

	init_nprint_map(&row, &col, &i, &j);
	while (i < len)
	{
		if (col && col % LINE_LENGTH == 0)
		{
			row++;
			col = 0;
		}
		if (!col || col % LINE_LENGTH != 0)
		{
			wattron(visu->vm, COLOR_PAIR(visu->owner[i].owner + 1) | A_BOLD);
			mvwprintw(visu->vm, OFFSET_LINES + row,
					OFFSET_COLS + col, "%02hhx ", visu->cor->map[i]);
			wattroff(visu->vm, COLOR_PAIR(visu->owner[i].owner + 1) | A_BOLD);
		}
		col += 3;
		i++;
	}
}

void	print_champ_area(t_visu *visu, int64_t curr_add)
{
	int		curr_add_modulo;

	curr_add_modulo = curr_add * 3;
	wattron(visu->vm, COLOR_PAIR(visu->owner[curr_add].owner + 1)
			| A_BOLD | A_REVERSE);
	mvwprintw(visu->vm, (OFFSET_LINES + (curr_add_modulo / LINE_LENGTH) + 1),
			OFFSET_COLS + (curr_add_modulo % LINE_LENGTH), "%02hhx",
			visu->cor->map[curr_add]);
	wattroff(visu->vm, COLOR_PAIR(visu->owner[curr_add].owner + 1)
			| A_BOLD | A_REVERSE);
}
