/*
 * header file for the typing game
 * christian torralba
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>



//using the fisher-yates shuffle
void shuffle(char* arr[])
{
	//keeping a temp vaiable so we dont loose any elements
	char* temp;

	//gettin size of array
	int arrSize = sizeof(*arr)/sizeof(*arr[0]);

	for(int i = arrSize - 1; i > 0; --i)
	{ 
		//generate random number
		int j = rand() % (i+1);	

		//swap the two elements
		char* temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}


