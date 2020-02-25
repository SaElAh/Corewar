/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   introduce_champs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:45:51 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/25 21:45:52 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "op.h"

void	introduce_champs(t_cor *cor)
{
	uint8_t	i;

	i = (uint8_t)cor->nb_champs;
	if (i)
		ft_printf("Introducing contestants...\n");
	while (i)
	{
		--i;
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
			(int32_t)(UINT_MAX - cor->champ[i].id_champ + 1),
			cor->champ[i].header.prog_size,
			cor->champ[i].header.prog_name, cor->champ[i].header.comment);
	}
}
