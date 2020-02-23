/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 16:52:07 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/23 16:41:33 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		ft_visu(t_cor *cor, t_visu *visu)
{
	int8_t		fd_1;
	int8_t		fd_2;

	initscr();
	curs_set(0);
	init_colors();
	get_info(visu, cor);
	fd_1 = call_open("./ncurses/corewar");
	fd_2 = call_open("./ncurses/mmask");
	windows_mgmt(visu, fd_1, fd_2);
	close(fd_1);
	close(fd_2);
	return (0);
}
