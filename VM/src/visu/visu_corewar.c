/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 16:52:07 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/25 19:21:30 by cghanime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"

void	print_dashboard(t_visu *visu)
{
	int32_t i;

	i = -1;
	visu->time1.tv_sec = 0;
	visu->time1.tv_nsec = 10000000L;
	wattron(visu->dash, COLOR_PAIR(5));
	mvwprintw(visu->dash, 29, 7, "Nb Cycles : %4d", visu->cor->nb_cycles);
	while (++i < (int)visu->cor->nb_champs)
		mvwprintw(visu->dash, 30 + i, 7, "Champ %d last cycle to live : %d",
			i + 1, visu->cor->champ[i].last_cycle_live);
	nanosleep(&visu->time1, &visu->time2);
	mvwprintw(visu->dash, 34, 7, "Cycle to die : %4d", visu->cor->cycles_to_die);
	mvwprintw(visu->dash, 35, 7, "Cycle to die ref : %4d",
		visu->cor->cycles_to_die_ref);
}

 void	print_winner(t_visu *visu, int ind_winner)
 {
	 char c;

	 wattron(visu->dash, COLOR_PAIR(6));
	 mvwprintw(visu->dash, 50, 7, "And the winner is ... Champion %s", visu->cor->champ[ind_winner].header.prog_name);
	 wrefresh(visu->dash);
	 while (read(0, &c, 1) != -1 &&  c != ' ')
	 	;
 }

static void	kill_window(void)
{
	endwin();
}

int		ft_visu(t_cor *cor, t_visu *visu)
{
	int8_t		fd_1;
	int8_t		fd_2;

	if (!(fd_1 = call_open("./src/visu/visu_utils/corewar")))
		return (1);
	if (!(fd_2 = call_open("./src/visu/visu_utils/mmask")))
	{
		close(fd_1);
		return (1);
	}
	if (!initscr())
	{
		close(fd_1);
		close(fd_2);
		ft_exit("initscr: failed to init window", EXIT_FAILURE);
	}
	ft_atexit(kill_window);
	curs_set(0);
	init_colors();
	get_info(visu, cor);
	windows_mgmt(visu, fd_1, fd_2);
	close(fd_1);
	close(fd_2);
	return (0);
}
