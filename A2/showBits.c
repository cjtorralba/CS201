/*
 *code by christian torralba
 *assignment number two for cs201 at PSU
 * purpose of this code is to take two command line arguments which are 
 * two hexadecimal values 
 * we then display the matching bits, the hexadecimal value of the compared arguments
 * as well as the signed and unsigned integer value
 */

#include <stdlib.h>
#include <stdio.h>



//this function take two arguments both unsigned ints 
//and returns a new unsigned int of matching bits
//as well as prints the matching bits
unsigned int printAndReturnMatches(unsigned int hex1, unsigned int hex2)
{
	unsigned int matching = hex1 & hex2;	//getting matching bits
	for(int i = 0; i < sizeof(matching) * 8; ++i)
	{
		if(((matching >> i) & 1) == 1)	//printing bits that are on (have value 1)
			printf("%d, ", i);
	}
	printf("in common\n");
	return matching;
}

//this function take an array of characters as an argument and returns the hexadecimal value
//in an unsigned int
unsigned int stringToHex(char* string)
{
	return (unsigned int) strtoul(string, (char**) NULL, 16);
}



int main(int argc, char** argv)
{
	//these are the values that will be used to store the command line arguments and 
	//matches between them in the form of unsigned ints
	unsigned int hex1;
       	unsigned int hex2;
       	unsigned int matching;

	//gotta make sure the correct number of arguments are given
	if(argc <= 1 || argc > 3)
	{
		printf("Please use two valid hexadecimal numbers");
		exit(EXIT_FAILURE);
	}

	//turning command line arguments into integer values
	hex1 = stringToHex(argv[1]);
	hex2 = stringToHex(argv[2]);

	//this value contains the bits that hex1 and hex2 have in common using the '&' operator
	matching = printAndReturnMatches(hex1, hex2);

	printf("\nHex value: %x\n Unsigned: %u\n  Signed: %d\n", matching, matching, matching);

	exit(EXIT_SUCCESS);
}
