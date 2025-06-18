#include <stdio.h>

int main()
{
	unsigned char c;
	char ch = 'A';
	int	i;
	c = 0;
	i = 7;
	while (1)
	{		

		printf("%i\n", ((ch >> i) & 1));

		// c = 
		if (i-- == 0) break;
	}
}