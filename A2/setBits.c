/*
 * code by christian torralba sophmore at PSU
 * part of assignment two for cs201 systems programming
 * The purpose of this program is to take a series of numbers as command line arguments,
 * these numbers can range from 0-15
 * we then set the bits of the each position in an integer
 */

#include <stdlib.h>
#include <stdio.h>

//defining size for each of use
#define SHORT_SIZE sizeof(unsigned short) * 8

void populateArray(int* array, char** argv, int argc)
{
	for(int i = 0; i < argc; i++)
	{
		if(i + 1 < argc)
		{
			int argument = (int) strtol(argv[i+1], (char**)NULL, 10);
			if(argument < 0 || argument > 15)
				exit(EXIT_FAILURE);
			else
				array[i] = argument;
		}

	}
}	

int main(int argc, char** argv)
{

	int arrSize = argc - 1;	//size of array, how many arguments - 1 for the a.out value
	unsigned short myShort; //short we are going to be flipping the bits in

//	int bitPosition;	//the bit position we are going to be manipulating

	if(arrSize <= 0)	//if there were no arguments passed in
	{
		printf("Please run again with proper command line arguments");
		exit(EXIT_FAILURE);
	}

	myShort = 0;

	int positions[arrSize];	//array of positions

	populateArray(positions, argv, argc);

	//setting the bit
	for(int i = 0; i < arrSize; ++i)
		myShort = myShort | (1 << positions[i]);

	//telling the user which bits were set
	printf("You flipped the bits in positions: ");
	for(int i = 0; i < arrSize; ++i)
		printf("%d, ", positions[i]);
	printf("\n\n");

	int values[SHORT_SIZE] = {0};

	for(int i = 0; i < SHORT_SIZE; ++i)
	{
		values[i] = (myShort >> i) & 1;	
	}

	for(int i = SHORT_SIZE-1; i > 0; --i)
	{
		printf("Values[%d]: %d\n", i, values[i]);
	}
	

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
