#include "libft.h"

void	usage(char *name)
{
	ft_printf("Usage: %s [-d N -s N -v N] <[-n N] champ.cor> ...\n", name);
	ft_printf("		-d N:	Dumps memory after N cycles then exits\n");
	ft_printf("		-s N:	Runs N cycles, dumps memory, pauses, "
			"then repeats\n");
	ft_printf("		-g  :	Graphical version of the Virtual Machine\n");
	ft_printf("		-v N:	Verbosity levels, can be added together to "
		"enable several\n");
	ft_printf("			- 0: Show only essentials\n");
	ft_printf("			- 1: Show lives\n");
	ft_printf("			- 2: Show cycles\n");
	ft_printf("			- 4: Show operations\n");
	ft_printf("			- 8: Show deaths\n");
	ft_printf("			- 16: Show PC movements\n");
}
