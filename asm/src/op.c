/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:34:43 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/18 15:48:57 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

const t_op	g_op_tab[OP_COUNT + 1] =
{
	{"live", 1, {T_DIR}, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 0},
	{"zjmp", 1, {T_DIR}, 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 1},
	{"fork", 1, {T_DIR}, 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 1},
	{"lfork", 1, {T_DIR}, 0, 1},
	{"aff", 1, {T_REG}, 1, 0},
	{0, 0, {0}, 0, 0}
};
