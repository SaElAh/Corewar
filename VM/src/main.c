
#include "op.h"

int		main(int ac, char **av)
{
	t_cor	corewar;
	t_visu	visu;

	corewar = (t_cor){};
	if (init_corewar(&corewar, ac, av))
	{
		free_champs_process(&corewar);
		return (1);
	}
	introduce_champs(&corewar);
	if (corewar.graphic)
		ft_visu(&corewar, &visu);
	ft_exec_champs(&corewar, &visu);
	if (corewar.graphic)
	{
		endwin();
		free(visu.vm);
		free(visu.dash);
	}
	return (0);
}
