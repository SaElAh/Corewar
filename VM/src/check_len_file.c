
#include <unistd.h>
#include <stdio.h>
#include "op.h"

int		check_len_file(int file, char *av)
{
	off_t offset;

	if ((offset = lseek(file, 0, SEEK_END))
		< (long long int)sizeof(t_header))
	{
		ft_printf("Error: File %s is too small to be a champion\n", av);
		return (1);
	}
	offset = lseek(file, -offset, SEEK_CUR);
	if (offset)
	{
		ft_printf("PB AVEC LSEEK !!!! offset = %lld\n", offset);
		return (1);
	}
	return (0);
}
