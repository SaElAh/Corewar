/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cghanime <cghanime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:41:30 by cghanime          #+#    #+#             */
/*   Updated: 2020/02/23 18:36:12 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"

static t_pro	*create_forked_process(t_cor *cor, t_pro *forking_pro)
{
	t_pro	*new;

	if (!(new = (t_pro *)ft_secmalloc(sizeof(t_pro))))
		return (NULL);
	ft_memcpy((void *)new, (void *)forking_pro, sizeof(t_pro));
	cor->biggest_ind_pro += 1;
	new->index_pro = cor->biggest_ind_pro;
	new->next = cor->tab_process[cor->curr_ind_process];
	if (cor->tab_process[cor->curr_ind_process])
		cor->tab_process[cor->curr_ind_process]->prev = new;
	cor->tab_process[cor->curr_ind_process] = new;
	new->prev = NULL;
	return (new);
}

int				ft_fork(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];
	t_pro	*new;
	int		curr_add;

	curr_add = pro->curr_add;
	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){11, curr_add});
	new = create_forked_process(cor, pro);
	new->curr_add = curr_add + (args[0].value % IDX_MOD);
	adjust_curr_add(&new->curr_add);
	return (0);
}

int				ft_lfork(t_cor *cor, t_pro *pro)
{
	t_args	args[MAX_ARGS_NUMBER];
	t_pro	*new;
	int		curr_add;

	curr_add = pro->curr_add;
	if (read_args(args, cor, pro))
		return (1);
	print_op(cor, args, pro, (int[2]){14, curr_add});
	new = create_forked_process(cor, pro);
	new->curr_add = curr_add + args[0].value;
	adjust_curr_add(&new->curr_add);
	return (0);
}
