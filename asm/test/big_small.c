#include <stdio.h>
#include <stdlib.h>

void	dec_to_bin(int nb, unsigned char bin[4])
{
	int				i;
	unsigned char	*ptr;

	i = -1;
	ptr = (unsigned char *)&nb;
	while (++i < 4)
		bin[i] = ptr[i];
}

int	main(int argc, char **argv)
{
	int				nb;
	unsigned char	bin[4];

	if (argc < 2)
		return (1);
	nb = atoi(argv[1]);
	dec_to_bin(nb, bin);
	printf("hex: ");
	for (int i = 0; i < 4; ++i)
		printf("%.2x", bin[i]);
	printf("\nbin:");
	for (int i = 0; i < 4; ++i)
		for (int j = 7; j >= 0; j-=4)
			printf(" %d%d%d%d", (bin[i] >> j & 1), (bin[i] >> (j - 1) & 1),
				(bin[i] >> (j - 2) & 1), (bin[i] >> (j - 3) & 1));
	printf("\n");
	return (0);
}
