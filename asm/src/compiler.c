/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 13:09:40 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/18 21:04:16 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"
#include "errors.h"

static void	write_arg_bytes(t_asmdata *adat, t_parsed_op *op,
				int value, unsigned int size)
{
	unsigned char	*bin;

	bin = (unsigned char *)&value;
	while (op->address + op->len < CHAMP_MAX_SIZE && size)
		adat->prog[op->address + op->len++] = bin[--size];
}

static int	parse_arg(unsigned char *arg_types, t_parsed_op *op,
						unsigned int i, unsigned int *size)
{
	unsigned char	type;
	int				value;

	value = 0;
	if (op->args[i]->id == I_REGISTER)
		type = REG_CODE;
	else if (op->args[i]->id == I_DIRECT || op->args[i]->id == I_DIRECT_LABEL)
		type = DIR_CODE;
	else
		type = IND_CODE;
	if (op->args[i]->id != I_DIRECT_LABEL && op->args[i]->id != I_INDIRECT_LABEL)
		value = ft_atoi(op->args[i]->str
			+ (type == DIR_CODE || type == REG_CODE));
	else
		op->label_add[i] = op->len;
	if (type == IND_CODE
		|| (type == DIR_CODE && g_op_tab[op->op_code - 1].mod_tdir_size))
		*size = IND_BYTE_SIZE;
	else if (type == REG_CODE)
		*size = REG_BYTE_SIZE;
	else
		*size = DIR_BYTE_SIZE;
	if (arg_types)
		*arg_types |= (type << (1 + 2 - i) * 2);
	return (value);
}

static void	compile_inst_args(t_asmdata *adat, t_parsed_op *op)
{
	unsigned char	*arg_types;
	int				value;
	unsigned int	size;
	unsigned int	i;

	i = 0;
	arg_types = g_op_tab[op->op_code - 1].arg_type_code ?
		adat->prog + op->address + op->len++ : NULL;
	while (op->address + op->len < CHAMP_MAX_SIZE && i < op->argc)
	{
		value = parse_arg(arg_types, op, i, &size);
		write_arg_bytes(adat, op, value, size);
		++i;
	}
}

static void	compile_instructions(t_asmdata *adat)
{
	unsigned int	address;
	size_t			i;

	address = 0;
	i = 0;
	while (i < adat->ops_len)
	{
		adat->ops[i].len = 0;
		adat->ops[i].address = address;
		adat->prog[address + adat->ops[i].len++] = adat->ops[i].op_code;
		compile_inst_args(adat, &adat->ops[i]);
		if ((address += adat->ops[i].len) > CHAMP_MAX_SIZE)
			ft_exit("compiler: program too big\n", E_PROGRAM_TOO_BIG);
		++i;
	}
	adat->prog_size = address;
}

void		compiler(t_asmdata *adat)
{
	(void)adat;
	compile_instructions(adat);
	compile_labels(adat);
	write_exec_file(adat);
}
