/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:46:09 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/25 21:47:46 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <fcntl.h>
#include <sys/errno.h>
#include "op.h"
#include "libft.h"

int64_t	ft_atol(const char *str)
{
	int			i;
	uint64_t	nb;

	i = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		str++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') || nb > UINT_MAX)
			return (-1);
		else
		{
			nb = (nb * 10) + str[i] - '0';
			i++;
		}
	}
	return (nb);
}

int		read_binary(char *av, t_champ *champ)
{
	int		file;
	int		check_err;

	check_err = 0;
	if ((file = open(av, O_RDONLY, O_NOFOLLOW | O_NONBLOCK)) < 0)
	{
		ft_printf("%s: %s\n", av, strerror(errno));
		check_err = 1;
	}
	if (check_err || check_len_file(file, av) || read_magic(file, champ, av)
			|| read_prog_name(file, champ, av)
			|| read_prog_size(file, champ, av)
			|| read_comment(file, champ, av) || read_prog(file, champ, av))
		check_err = 1;
	close(file);
	return (check_err);
}

int		add_champ(char *champ_file, t_cor *cor)
{
	int		i;

	i = cor->nb_champs;
	if (++cor->nb_champs > MAX_PLAYERS)
	{
		ft_dprintf(2, "too many champions, only %d allowed\n", MAX_PLAYERS);
		return (1);
	}
	cor->champ[i].id_champ = !cor->champ[i].id_champ ?
		UINT_MAX - i : cor->champ[i].id_champ;
	cor->champ[i].index_champ = i;
	if (read_binary(champ_file, &cor->champ[i]))
		return (1);
	return (0);
}

void	parse_option(int c, char *arg, t_cor *cor)
{
	int64_t	value;

	if (c == 'g')
		cor->graphic = 1;
	else
	{
		if ((value = ft_atol(arg)) < 0)
			ft_dprintf(2, "invalid value for option '%c': '%s'\n", c, arg);
		else if (c == 'd')
		{
			cor->nb_cycles_dump = value;
			cor->dump_opt = 1;
		}
		else if (c == 's')
			cor->show_opt = (uint32_t)value;
		else if (c == 'v')
			cor->verbose |= (uint16_t)(value & 0xff);
		else if (c == 'n')
			cor->champ[cor->nb_champs].id_champ = UINT_MAX
												- (uint64_t)value + 1;
	}
}

int		parse_arguments(int argc, char **argv, t_cor *cor)
{
	int			c;
	t_optdata	od;

	init_getopt(&od, OPT_STRING, NULL, NULL);
	while (od.optind < argc)
	{
		if ((c = ft_getopt(argc, argv, &od)) != -1)
		{
			if (c == ':')
				ft_dprintf(2, "no argument given for '%c' option\n", od.optopt);
			else if (c == '?')
				ft_dprintf(2, "unknown option: '%c'\n", od.optopt);
			else
				parse_option(c, od.optarg, cor);
		}
		else if (add_champ(argv[od.optind++], cor))
			return (1);
	}
	return (0);
}
