#include <stdio.h>
#include <limits.h>
#include <stdint.h>

#define STRLOL "+-+-"

struct s_lol
{
	char *i;
	int	*o;
};

struct s_prout
{
	struct s_lol s;
	int a;
	int b;
	int c;
	char *str;
};

void	print_bits(void *ptr, int size)
{
	unsigned char *tmp = (unsigned char *) ptr;
	int i = size - 1;
	int j;
	char c;

	while (i >= 0)
	{
		j = 7;
		while (j >= 0)
		{
			c = ((tmp[i] >> j) & 1) + 48;
			printf("%c", c);
			j--;	
		}
		printf(" ");
		i--;
	}
	printf("\n");
}
#include <limits.h>

int		main()
{
	int32_t	i = -1;
	int j = i;
	char	*lol = (void*)-12;
	struct s_prout p;
	

	p = (struct s_prout){};
	printf("%p\n", lol);

	(void)p;
	int res = i % 512;
	int res2 = i & 511;
	printf("j %i:\n", j);
	print_bits(&j, 4);
	printf("i :\n");
	print_bits(&i, 4);
	printf("res 1 =  %d :\n", res);
	print_bits(&res, 4);
	printf("res 2 = %d:\n", res2);
	print_bits(&res2, 4);
	printf("[%c][%c]\n", STRLOL[0], STRLOL[1]);
	return (0);
}
