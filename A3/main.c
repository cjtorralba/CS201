/*
 * code written by christian torralba for cs201, this is assignment three
 * purpose of this program is to take three command line arguments and create a loating point number from them
 * this code teests for denormalized and special cases as well
 */




#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


//returns true if the arguments can be used in this program, 
//false otherwise
bool isValid(int frac, int exp)
{
	return !((frac < 2 || frac > 10) || (exp < 3 || exp > 5));
}

bool hexIsValid(int frac, int exp, int hex)
{
	int maxBitsAllowed = frac + exp + 1;
	return ((int)log2(hex)+1) <= maxBitsAllowed;
}

//prints bits of num, returns number of bits displayed
void printBits(int num, int numOfBits)
{
	for(int i = numOfBits; i >= 0; --i)
	{
		printf("%d", (num >> i) & 1);
	}
}


//making a mask to get fraction field out of hex value
int fracMask(int fracBits)
{
	int fracMask = 0;
	for(int i = 0; i < fracBits; ++i)
		fracMask |= (1 << i);
	return fracMask;
}


//making a mask to get exponent field out of hex value
int expMask(int expBits, int fracBits)
{
	int expMask = 0;
	for(int i = fracBits; i < (fracBits + expBits); ++i)
		expMask |= (1 << i);	
	return expMask;
}



//check to see if value is denormalized
bool isDenormalized(int exp, int expBits)
{
	bool returnVal = false;

	//tracking number of ones and zeroes
	int numZeros = 0;

	for(int i = 0; i < expBits; ++i)
	{
		if(((exp >> i) & 1) == 0)
			++numZeros;
	}
	if(numZeros == expBits)
		returnVal = true;
	return returnVal;
}


//checking to see if the value is special
bool isSpecial(int exp, int expBits)
{
	bool returnVal = false;

	//tracking number of ones and zeroes
	int numOnes = 0;

	for(int i = 0; i < expBits; ++i)
	{
		if(((exp >> i) & 1) == 1)
			++numOnes;
	}
	printf("Num of ones: %d\nExpBits: %d\n", numOnes,  expBits);
	if(numOnes == expBits)
		returnVal = true;
	return returnVal;
}



//checking to see if fraction field has all zeros
bool fractionAllZeros(int frac, int fracBits)
{
	bool allZeros = true;
	
	for(int i = 0; i < fracBits; ++i)
	{
		if(((frac >> i) & 1) == 1)
			allZeros = false;
	}
	return allZeros;
}



int main(int argc, char** argv)
{

	//must check for correct command line arguments first
	if(argc <= 1 || argc > 4)	//only a.out, or more args than required
	{
		printf("Correction usage: ./a.out <# of frac_bits> <# of exp_bits> <hex value>\n");
		exit(EXIT_FAILURE);
	}

	int fracBits = 0;	//holds number of fraction bits, between 2 and 10 
	int expBits = 0;	//holds the number of exponent bits, between 3 and 5 ALSO KNOWN AS 'K' VALUE
	int hexValue = 0;	//holds the hexadecimal value of the number we want to parse

	//parsing the command line arguments into the vaiables
	sscanf(argv[1], "%d", &fracBits);
	sscanf(argv[2], "%d", &expBits);
	sscanf(argv[3], "%x", &hexValue);

	//checking to make sure vaiables are valid
	if(!isValid(fracBits, expBits) || !hexIsValid(fracBits, expBits, hexValue))
	{
		printf("Please enter valid command line arguments\n");
		exit(EXIT_FAILURE);
	}



	//sign plus fraction field plus exponent field
	int totalBits = fracBits + expBits;

	//getting fractional field
	int fractionMask = fracMask(fracBits);
	int fracField = fractionMask & hexValue;

	//getting exponent mask	
	int exponentMask = expMask(expBits, fracBits);
	int expField = (exponentMask & hexValue) >> fracBits;



	//---------Calculating values for IEEE---------
	int bias = pow(2, (expBits - 1)) - 1;	
	int E;
	int sign = (hexValue >> totalBits) & 1;
	double fractionValue = 0;
	double M;
	double V;

	if(!isDenormalized(expField, expBits) && !isSpecial(expField, expBits))
	{
		//setting value E
		E = expField - bias;

		//calculating frac value
		fractionValue = 0;
		int power = 1;
		for(int i = fracBits - 1; i >= 0; --i)
		{
			if((fracField >> i) & 1)
				fractionValue += pow(2, (power * -1));
			++power;
		}

		M = 1 + fractionValue;

		//calculating final number
		V = pow(-1, sign) * M * pow(2, E);
	}
	else if(isDenormalized(expField, expBits))
	{
		E = 1 - bias;
		fractionValue = 0;
		int power = 1;
		for(int i = fracBits - 1; i >= 0; --i)
		{
			if((fracField >> i) & 1)
				fractionValue += pow(2, (power * -1));
			++power;
		}

		M = fractionValue;

		//calculating final number
		V = pow(-1, sign) * M * pow(2, E);
	}
	else if(isSpecial(expField, expBits))
	{
		if(fractionAllZeros(fracField, fracBits))
		{
			if(sign == 0)
				printf("+inf");
			else
				printf("-inf");
		}
		else
			printf("NaN");
		exit(EXIT_SUCCESS);

	}

	printf("\n\nV = %lf\n", V);

	exit(EXIT_SUCCESS);
}
