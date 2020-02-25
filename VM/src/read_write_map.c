/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:46:27 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/25 21:46:28 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		read_map(uint8_t map[MEM_SIZE], int64_t address)
{
	uint8_t	*valptr;
	int		value;
	int		i;

	valptr = (uint8_t *)&value;
	value = 0;
	i = -1;
	while (++i < REG_SIZE)
	{
		adjust_curr_add(&address);
		valptr[REG_SIZE - 1 - i] = map[address++];
	}
	return (value);
}

void	write_map(t_cor *cor, int64_t address, int value, int index_champ)
{
	uint8_t	*valptr;
	int		i;

	valptr = (uint8_t *)&value;
	i = -1;
	while (++i < REG_SIZE)
	{
		adjust_curr_add(&address);
		cor->owner[address] = index_champ;
		cor->map[address++] = valptr[REG_SIZE - 1 - i];
	}
}
