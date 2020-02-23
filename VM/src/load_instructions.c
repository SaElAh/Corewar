
#include "op.h"

int		ft_ld(t_cor *cor, t_pro *pro)
{
	t_args		args[MAX_ARGS_NUMBER];
	int			curr_add;
	int64_t		curr_addtmp;
	int			tmp1;

	curr_add = pro->curr_add;
	if (read_args(args, cor, pro))
		return (1);
	curr_addtmp = curr_add + (args[0].value) % IDX_MOD;
	adjust_curr_add(&curr_addtmp);
	tmp1 = read_map(cor->map, curr_addtmp);
	print_op(cor, args, pro, (int[2]){1, curr_add});
	print_args(cor, args, g_op_tab[1].nb_args, pro->carry);
	pro->reg[args[1].value - 1] = args[0].type == DIR_CODE ? args[0].value
		: tmp1;
	pro->carry = !pro->reg[args[1].value - 1];
	return (0);
}

int		ft_ldi(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];
	int		curr_add;
	int		val[2];
	int		i;

	curr_add = pro->curr_add;
	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){9, curr_add});
	print_args(cor, args, g_op_tab[9].nb_args, pro->carry);
	i = -1;
	while (++i < 2)
	{
		if (args[i].type == REG_CODE)
			val[i] = pro->reg[args[i].value - 1];
		else if (args[i].type == DIR_CODE)
			val[i] = args[i].value;
		else
			val[i] = read_map(cor->map, curr_add + (args[i].value % IDX_MOD));
	}
	pro->reg[args[2].value - 1] = read_map(cor->map, curr_add
		+ ((val[0] + val[1]) % IDX_MOD));
	return (0);
}

int		ft_lld(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];
	int		curr_add;
	uint8_t	*tmp;

	curr_add = pro->curr_add;
	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){12, curr_add});
	print_args(cor, args, g_op_tab[12].nb_args, pro->carry);
	pro->reg[args[1].value - 1] = args[0].type == DIR_CODE ? args[0].value
		: read_map(cor->map, curr_add + args[0].value);
	if (args[0].type == IND_CODE)
	{
		tmp = (uint8_t*)&pro->reg[args[1].value - 1];
		tmp[0] = tmp[2];
		tmp[1] = tmp[3];
		tmp[3] = 0;
		tmp[2] = 0;
	}
	pro->carry = !pro->reg[args[1].value - 1];
	return (0);
}

int		ft_lldi(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];
	int		curr_add;
	int		val[2];
	int		i;

	curr_add = pro->curr_add;
	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){13, curr_add});
	print_args(cor, args, g_op_tab[13].nb_args, pro->carry);
	i = -1;
	while (++i < 2)
	{
		if (args[i].type == REG_CODE)
			val[i] = pro->reg[args[i].value - 1];
		else if (args[i].type == DIR_CODE)
			val[i] = args[i].value;
		else
			val[i] = read_map(cor->map, curr_add + (args[i].value % IDX_MOD));
	}
	pro->reg[args[2].value - 1] = read_map(cor->map,
		curr_add + val[0] + val[1]);
	pro->carry = !pro->reg[args[2].value - 1];
	return (0);
}
