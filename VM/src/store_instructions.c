
#include "op.h"

int		ft_sti(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];
	int		curr_add;
	int		val[2];
	int		i;

	curr_add = pro->curr_add;
	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){10, curr_add});
	print_args(cor, args, g_op_tab[10].nb_args, pro->carry);
	i = 0;
	while (++i < 3)
	{
		if (args[i].type == REG_CODE)
			val[i - 1] = pro->reg[args[i].value - 1];
		else if (args[i].type == DIR_CODE)
			val[i - 1] = args[i].value;
		else
			val[i - 1] = read_map(cor->map, curr_add
				+ (args[i].value % IDX_MOD));
	}
	write_map(cor, curr_add + ((val[0] + val[1]) % IDX_MOD),
		pro->reg[args[0].value - 1], pro->index_champ);
	return (0);
}

int		ft_st(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];
	int		curr_add;

	curr_add = pro->curr_add;
	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){2, curr_add});
	print_args(cor, args, g_op_tab[2].nb_args, pro->carry);
	if (args[1].type == REG_CODE)
		pro->reg[args[1].value - 1] = pro->reg[args[0].value - 1];
	else
	{
		write_map(cor, curr_add + (args[1].value % IDX_MOD),
			pro->reg[args[0].value - 1], pro->index_champ);
	}
	return (0);
}
