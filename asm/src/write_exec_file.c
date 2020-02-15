/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_exec_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 21:05:30 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/15 13:31:58 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_asmdata.h"
#include "errors.h"
#include <fcntl.h>
#include <stdio.h>

static int	write_int(unsigned int value, int fd)
{
	unsigned char	*bin;
	int				i;

	bin = (unsigned char *)&value;
	i = 4;
	while (i)
		if (write(fd, bin + --i, 1) < 0)
			return (-1);
	return (0);
}

void		write_exec_file(t_asmdata *adat)
{
	char	*name;
	size_t	len;
	int		fd;

	len = ft_strlen(adat->file_name);
	name = ft_strncpy(ft_strnew(len + 2), adat->file_name, len - 2);
	ft_strcat(name, ".cor");
	ft_printf("Writing output program to %s\n", name);
	if ((fd = open(name, O_CREAT | O_WRONLY, 0666)) == -1)
	{
		perror("open");
		ft_exit(NULL, E_OPEN_FILE);
	}
	if (write_int(COREWAR_EXEC_MAGIC, fd) < 0
		|| write(fd, adat->prog_name, PROG_NAME_LENGTH + NULL_SEP) < 0
		|| write_int(adat->prog_size, fd) < 0
		|| write(fd, adat->comment, COMMENT_LENGTH + NULL_SEP) < 0
		|| write(fd, adat->prog, adat->prog_size) < 0)
	{
		perror("write");
		ft_exit(NULL, E_WRITE_ERROR);
	}
	close(fd);
}
