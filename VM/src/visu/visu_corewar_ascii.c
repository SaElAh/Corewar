/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_corewar_ascii.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 17:07:01 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/23 18:37:31 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "op.h"

int8_t	call_open(char *path)
{
	int8_t	fd;

	if ((fd = open(path,
		O_RDONLY, O_NOFOLLOW | O_NONBLOCK)) == -1)
	{
		write(2, "Error while opening file\n", 25);
		return (0);
	}
	return (fd);
}

int		read_corewar(int fd, WINDOW *win, int8_t offset)
{
	char	*line;
	int		i;

	i = 1;
	while (get_next_line(fd, &line) > 0)
	{
		mvwprintw(win, i++, offset, "%s\n", line);
		ft_memdel((void **)&line);
	}
	line = NULL;
	get_next_line(fd, &line);
	if (line)
	{
		mvwprintw(win, i++, offset, "%s\n", line);
		ft_memdel((void **)&line);
	}
	return (EXIT_SUCCESS);
}

void	windows_mgmt(t_visu *visu, int8_t fd_1, int8_t fd_2)
{
	wattron(visu->vm, COLOR_PAIR(ASCII) | A_BOLD);
	read_corewar(fd_1, visu->vm, 60);
	wattroff(visu->vm, COLOR_PAIR(ASCII) | A_BOLD);
	wattron(visu->dash, COLOR_PAIR(COLOR_BLUE));
	read_corewar(fd_2, visu->dash, 7);
	wattroff(visu->dash, COLOR_PAIR(COLOR_BLUE));
	wattron(visu->vm, COLOR_PAIR(ASCII) | A_BOLD);
	wborder(visu->vm, '#', '#', '#', '#', '#', '#', '#', '#');
	wattroff(visu->vm, COLOR_PAIR(ASCII) | A_BOLD);
	wattron(visu->dash, COLOR_PAIR(J4) | A_BOLD);
	wborder(visu->dash, 'R', 'E', 'O', 'A', 'C', 'R', 'R', 'W');
	wattroff(visu->dash, COLOR_PAIR(J4) | A_BOLD);
}
