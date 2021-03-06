/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:46:23 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/25 21:46:25 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <limits.h>
#include "libft.h"
#include "op.h"

int		read_magic(int file, t_champ *champ, char *av)
{
	uint32_t	magic;
	char		buffer[4];

	magic = 0xf383ea00;
	if (read(file, buffer, 4) < 0)
	{
		ft_printf("ERROR IN READ magic\n");
		return (1);
	}
	if (lseek(file, 0, SEEK_CUR) != 4
		|| (magic & 0xff) != (buffer[0] & 0xff)
		|| ((magic >> 8) & 0xff) != (buffer[1] & 0xff)
		|| ((magic >> 16) & 0xff) != (buffer[2] & 0xff)
		|| ((magic >> 24) & 0xff) != (buffer[3] & 0xff))
	{
		ft_dprintf(2, "Error: File %s has an invalid header\n", av);
		return (1);
	}
	champ->header.magic = COREWAR_EXEC_MAGIC;
	return (0);
}

int		read_prog_name(int file, t_champ *champ, char *av)
{
	char	buffer[PROG_NAME_LENGTH];

	if (read(file, buffer, PROG_NAME_LENGTH) < 0)
	{
		ft_printf("ERROR IN READ prog name\n");
		return (1);
	}
	if (lseek(file, 4, SEEK_CUR) != sizeof(uint32_t) + PROG_NAME_LENGTH + 4)
	{
		ft_dprintf(2, "Error: File %s has an invalid header\n", av);
		return (1);
	}
	ft_memcpy(&champ->header.prog_name, buffer, PROG_NAME_LENGTH);
	return (0);
}

int		read_prog_size(int file, t_champ *champ, char *av)
{
	char	buffer[4];

	if (read(file, buffer, 4) < 0)
	{
		ft_printf("ERROR IN READ prog size\n");
		return (1);
	}
	if (lseek(file, 0, SEEK_CUR) != sizeof(uint32_t) * 2 + PROG_NAME_LENGTH + 4)
	{
		ft_dprintf(2, "Error: File %s has an invalid header\n", av);
		return (1);
	}
	champ->header.prog_size = ((0xff & buffer[0]) << 24)
		| ((0xff & buffer[1]) << 16) | ((0xff & buffer[2]) << 8)
		| (buffer[3] & 0xff);
	return (0);
}

int		read_comment(int file, t_champ *champ, char *av)
{
	char	buffer[COMMENT_LENGTH];

	if (read(file, buffer, COMMENT_LENGTH) < 0)
	{
		ft_printf("ERROR IN READ comment\n");
		return (1);
	}
	if (lseek(file, 4, SEEK_CUR) != sizeof(t_header))
	{
		ft_dprintf(2, "Error: File %s has an invalid header\n", av);
		return (1);
	}
	ft_memcpy(&champ->header.comment, buffer, COMMENT_LENGTH);
	return (0);
}

int		read_prog(int file, t_champ *champ, char *av)
{
	char		buffer[CHAMP_MAX_SIZE * 2];
	uint32_t	len;

	if ((len = read(file, buffer, CHAMP_MAX_SIZE * 2)) < 0)
	{
		ft_printf("ERROR IN READ read prog\n");
		return (1);
	}
	if (len != champ->header.prog_size)
	{
		ft_dprintf(2, "Error: File %s has a code size that differs from what \
its header says\n", av);
		return (1);
	}
	else if (len > CHAMP_MAX_SIZE)
	{
		ft_dprintf(2, "Error: File %s has too large a code (%u > %u)\n",
				av, len, CHAMP_MAX_SIZE);
		return (1);
	}
	ft_memcpy(&champ->prog, buffer, len);
	return (0);
}
