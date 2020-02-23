
#include "op.h"
#include <stdio.h>

void			verbose_pc(t_pro *tmp, t_cor *cor, int64_t tmp_add)
{
	int	i;

	if (cor->verbose & VERBOSE_PC && (tmp->curr_char != 9
			|| (tmp->curr_char == 9 && !tmp->carry)))
	{
		if (tmp->curr_add - tmp_add == 2)
			return ;
		printf("ADV %lli (0x%.4llx -> 0x%.4llx) ",
				tmp->curr_add - tmp_add, tmp_add, tmp->curr_add);
		i = 0;
		while (i < tmp->curr_add - tmp_add)
		{
			printf("%.2x ", cor->map[i + tmp_add]);
			i++;
		}
		printf("\n");
	}
}
