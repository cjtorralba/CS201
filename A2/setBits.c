/*
 * code by christian torralba sophmore at PSU
 * part of assignment two for cs201 systems programming
 * The purpose of this program is to take a series of numbers as command line arguments,
 * these numbers can range from 0-15
 * we then set the bits of the each position in an integer
 */

#include <stdlib.h>
#include <stdio.h>

//defining size for ease of use
#define SHORT_SIZE sizeof(unsigned short) * 8



//populating the array with values from argv, EXCLUDING "./a.out"
void populateArray(int* array, char** argv, int argc)
{
	for(int i = 0; i < argc; i++)
	{
		if(i + 1 < argc)
		{
			int argument = (int) strtol(argv[i+1], (char**)NULL, 10);
			if(argument < 0 || argument > 15)
			{
				printf("Please run again with valid command line inputs");
				exit(EXIT_FAILURE);
			}
			else
				array[i] = argument;
		}
	}
}	


//setting the bits in a short, taking an array of positions 
unsigned short setShort(int* positions, int arrSize)
{
	unsigned short toReturn = 0; //value we will be returning
	for(int i = 0; i < arrSize; ++i)
	{
		toReturn |= 1 << positions[i];	//setting bit in positions from positions array
//		printf("Setting bit in position: %d\n", positions[i]);
	}
	return toReturn;
}


//prints the number as a binary
void printBits(unsigned short toPrint)
{
	for(int i = SHORT_SIZE - 1; i >= 0; --i)
	{
		printf("%d", (toPrint >> i) & 1);
		if(i % 4 == 0)
			printf(" ");
	}
}



int main(int argc, char** argv)
{
	if(argc <= 1 || argc > 17)	//if there were no arguments passed in
	{
		printf("Please run again with proper command line arguments");
		exit(EXIT_FAILURE);
	}

	//short we are going to be setting bits in
	unsigned short myShort = 0;

	//size of array holding bit positions we will be flipping
	int arrSize = argc - 1;

	//array holding bit positions
	int positions[arrSize];
	//populating the array with variables from argv
	populateArray(positions, argv, argc);

	//setting the short, modifying the bits in it
	myShort = setShort(positions, arrSize);
	
	//printing the position of the bits that are set
	printf("You set the bits in positions: ");
	for(int i = 0; i < arrSize; ++i)
		printf("%d, ", positions[i]);
	printf("\n\n");

	//telling user what the integer value of the short is after setting the bits
	printf("The integer value of the unsigned short is: %d\n", myShort);

	//printing the binary version of the short
	printBits(myShort);

	exit(EXIT_SUCCESS);
}
