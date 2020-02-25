
#include "op.h"
#include "libft.h"

void	ft_check_winner(t_cor *cor, t_visu *visu)
{
	uint32_t	i;
	uint32_t	winner;
	uint32_t	last_cycle;
	uint32_t	ind_winner;

	i = 0;
	last_cycle = cor->champ[i].last_cycle_live;
	winner = cor->champ[i].index_champ;
	ind_winner = i;
	while (i < cor->nb_champs)
	{
		if (cor->champ[i].last_cycle_live >= last_cycle)
		{
			last_cycle = cor->champ[i].last_cycle_live;
			winner = cor->champ[i].index_champ;
			ind_winner = i;
		}
		i++;
	}
	print_winner(visu, ind_winner);
	ft_printf("Contestant %d, \"%s\", has won !\n",
		cor->nb_champs - ind_winner,
		cor->champ[ind_winner].header.prog_name);
	free_champs_process(cor);
}
