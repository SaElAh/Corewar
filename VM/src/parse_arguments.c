
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/errno.h>

#include "op.h"

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
	if (check_err || check_len_file(file, av) || read_magic(file, champ)
			|| read_prog_name(file, champ) || read_prog_size(file, champ)
			|| read_comment(file, champ) || read_prog(file, champ))
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
	{
		ft_dprintf(2, "error while reading champion file '%s'\n", champ_file);
		return (1);
	}
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
	int		c;

	while (optind < argc)
	{
		if ((c = getopt(argc, argv, ":d:s:v:n:g")) != -1)
		{
			if (c == ':')
				ft_dprintf(2, "no argument given for '%c' option\n", optopt);
			else if (c == '?')
				ft_dprintf(2, "unknown option: '%c'\n", optopt);
			else
				parse_option(c, optarg, cor);
		}
		else if (add_champ(argv[optind++], cor))
			return (1);
	}
	return (0);
}
