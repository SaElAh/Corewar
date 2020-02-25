
#include "op.h"
#include "libft.h"

static int		check_duplicates(t_cor *cor)
{
	uint32_t	tmp_id;
	uint32_t	nb_champs;
	uint32_t	cpt;

	nb_champs = 0;
	while (nb_champs < cor->nb_champs)
	{
		cpt = 0;
		tmp_id = cor->champ[nb_champs].id_champ;
		while (cpt < cor->nb_champs)
		{
			if (cpt != nb_champs)
			{
				if (cor->champ[cpt].id_champ == cor->champ[nb_champs].id_champ)
					return (1);
			}
			cpt++;
		}
		nb_champs++;
	}
	return (0);
}

int				check_champs(t_cor *cor, char *name)
{
	if (!cor->nb_champs)
	{
		usage(name);
		return (1);
	}
	if (check_duplicates(cor))
	{
		ft_printf("Champions with duplicate ID\n");
		return (1);
	}
	return (0);
}
