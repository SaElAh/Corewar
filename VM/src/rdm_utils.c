#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include "op.h"

int		champ_nb(uint32_t owner)
{
	if (owner == UINT_MAX)
		return (0);
	if (owner == UINT_MAX - 1)
		return (1);
	if (owner == UINT_MAX - 2)
		return (2);
	if (owner == UINT_MAX - 3)
		return (3);
	else
		return (4);
}

void	print_map(t_cor *cor)
{
	uint8_t		c;
	uint32_t	j;
	uint32_t	i;

	j = 0;
	i = -1;
	while (++i < MEM_SIZE)
	{
		c = cor->map[i];
		if (!(i % 64))
		{
			ft_printf("0x%.4x : ", j);
			j += 64;
		}
		ft_printf("%.2hhx ", c);
		if ((i % 64) == 63)
			ft_printf("\n");
	}
}
