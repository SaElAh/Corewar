
#include <stdio.h>

void	usage(char *name)
{
	printf("Usage: %s [-d N -s N -v N] <[-n N] champ.cor> ...\n", name);
	printf("	-d N:	Dumps memory after N cycles then exits\n");
	printf("	-s N:	Runs N cycles, dumps memory, pauses, then repeats\n");
	printf("    -g  :   Graphical version of the Virtual Machine\n");
	printf("	-v N:	Verbosity levels, can be added together to "
		"enable several\n");
	printf("		- 0: Show only essentials\n");
	printf("		- 1: Show lives\n");
	printf("		- 2: Show cycles\n");
	printf("		- 4: Show operations\n");
	printf("		- 8: Show deaths\n");
	printf("		- 16: Show PC movements\n");
}
