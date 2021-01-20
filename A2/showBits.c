#include <stdlib.h>
#include <stdio.h>


int main(int argc, char** argv)
{
	if(argc <= 1 || argc > 3)
	{
		printf("Please use two valid hexadecimal numbers");
		exit(EXIT_FAILURE);
	}

	int hex1 = (int) strtol(argv[1], (char**) NULL, 16);

	for(int i = 0; i < 4

	printf("%s is the decimal value: %d\n", argv[1], hex1);
	exit(EXIT_SUCCESS);
}
