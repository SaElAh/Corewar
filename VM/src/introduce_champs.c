
#include <limits.h>
#include <stdio.h>
#include "op.h"

void	introduce_champs(t_cor *cor)
{
	uint8_t	i;

	i = (uint8_t)cor->nb_champs;
	if (i)
		printf("Introducing contestants...\n");
	while (i)
	{
		--i;
		printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
			(int32_t)(UINT_MAX - cor->champ[i].id_champ + 1),
			cor->champ[i].header.prog_size,
			cor->champ[i].header.prog_name, cor->champ[i].header.comment);
	}
}
