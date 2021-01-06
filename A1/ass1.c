/*
 * assignment number one for portland state university cs201 class
 * systems programming, purpose of this program is to test hpow fast user can type 
 * the words we will be using are "The quick brown fox jumps over the lazy dog"
 *
 * this program will be making use of a makefile and the input and output streams
 *
 * writen by christian torralba
 * 1/5/2021
 */



#include "ass1.h"



int main()
{
	//variable to keep track of the time
	struct timeval start, end;

	//starting one timer at the begining of the program
	gettimeofday(&start, NULL);

	printf("Please type the words EXACTLY how they appear, then press enter");


	//since we already know the words we will be displaying to the user we can just put them in 
	//an array and store them
	char* words[9] = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};

	char c; 	//for clearing the buffer when reading input
	char input[100];//where we will store the user input;
	bool match = false;	//exit condition for the main loops

	//size of the array "words" just for ease
	int arrSize = sizeof(words)/sizeof(words[0]);

	//shuffling the array of words real fast
	shuffle(words);

		
	//this is the main part of the program where the user is tping in the words 
	//the system then compares them using strcmp()
	for(int i = 0; i < arrSize; ++i)
	{
		do
		{
			printf("\n%s:", words[i]);

			scanf("%s", input); 		//getting user input

			while((c = getchar()) != '\n' && c != EOF);	//clearing buffer
			
			if(strcmp(input, words[i]) == 0)	//in case the word is wrong
				match = true;
		}while(!match);
		match = false;	//exit condition
	}

	//getting the time when all the words have been entered correctly
	gettimeofday(&end, NULL);

	//calculating the time it took for the user to type all the words
	double remaining = ((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec) - start.tv_usec;
	int remainSec = end.tv_sec - start.tv_sec;
	int remainMSec = end.tv_usec - start.tv_usec;

//	printf("Seconds:%d and %d microseconds\n", remainSec, remainMSec);


//this version displays the whole number ex: 12.345 seconds
	printf("Time: %f\n", remaining / 1000000);


	return 0;
}
