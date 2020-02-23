
#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "op.h"

int		ft_live(t_cor *cor, t_pro *pro);
int		ft_ld(t_cor *cor, t_pro *pro);
int		ft_st(t_cor *cor, t_pro *pro);
int		ft_add(t_cor *cor, t_pro *pro);
int		ft_sub(t_cor *cor, t_pro *pro);
int		ft_and(t_cor *cor, t_pro *pro);
int		ft_or(t_cor *cor, t_pro *pro);
int		ft_xor(t_cor *cor, t_pro *pro);
int		ft_zjmp(t_cor *cor, t_pro *pro);
int		ft_ldi(t_cor *cor, t_pro *pro);
int		ft_sti(t_cor *cor, t_pro *pro);
int		ft_fork(t_cor *cor, t_pro *pro);
int		ft_lld(t_cor *cor, t_pro *pro);
int		ft_lldi(t_cor *cor, t_pro *pro);
int		ft_lfork(t_cor *cor, t_pro *pro);
int		ft_aff(t_cor *cor, t_pro *pro);

#endif
