#include <stdio.h>

int	main(void)
{
	unsigned char	str3[3] = {0x4c, 0x4f, 0x4c};
	unsigned char	str2[3] = {0x4c, 0x4f};
	unsigned char	str1[3] = {0x4c};

	printf("%c%c%c\n", str3[0], str3[1], str3[2]);
	printf("%c%c\n", str2[0], str2[1]);
	printf("%c\n", str1[0]);
	return (0);
}
