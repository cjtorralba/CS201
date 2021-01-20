#include <stdlib.h>
#include <stdio.h>

#define SHORT_SIZE sizeof(unsigned short) * 8


int main(int argc, char** argv)
{

	int arrSize = argc - 1;

	if(arrSize <= 0)
	{
		printf("Please run again with proper command line arguments");
		exit(EXIT_FAILURE);
	}


	unsigned short myShort = 0;

	int positions[arrSize];	//array of positions
	int bitPosition;		//the bit we are going to be manipulating


	//putting command line arguments into positions array
	for(int i = 0; i < argc; i++)
	{
		if(i + 1 < argc)
		{
			int argument = (int) strtol(argv[i+1], (char**)NULL, 10);
			if(argument < 0 || argument > 15)
				exit(EXIT_FAILURE);
			else
				positions[i] = argument;
		}
	}


	//setting the bit
	for(int i = 0; i < arrSize; ++i)
		myShort = myShort | (1 << positions[i]);

	//telling the user which bits were set
	printf("You flipped the bits in positions: ");
	for(int i = 0; i < arrSize; ++i)
		printf("%d, ", positions[i]);
	printf("\n\n");

	//printing the unsigned short as a binary number
	for(int i = 0; i < SHORT_SIZE; ++i)
	{
		if(i == 0);//do nothing, we dont want to add a space at the very start

		else if(i % 4 == 0)	//adding space after each 4 numbers for readability
			printf(" ");

		printf("%d", (myShort >> i) & 1);
	}

	printf("\nThe value of this binary number is: %d\n", myShort);

	exit(EXIT_SUCCESS);
}
