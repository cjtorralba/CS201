#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>




typedef struct menu
{
	bool isRunning;
	char** choices; 
	int items;
	int numEntries;
	long* entries;

}menu;








//essentially a constructor for the menu
menu* newMenu()
{
	menu* toReturn = (menu*) malloc(sizeof(menu));
	

	toReturn->isRunning = true;

	toReturn->items = 7;

	toReturn->choices = (char**) malloc(toReturn->items * sizeof(char*));

	toReturn->choices[0] = (char*) malloc(sizeof("exit") + 1);
	strncpy(toReturn->choices[0], "exit", sizeof("Exit"));

	toReturn->choices[1] = (char*) malloc(sizeof("Addition") + 1);
	strncpy(toReturn->choices[1], "Addition", sizeof("Addition"));

	toReturn->choices[2] = (char*) malloc(sizeof("Subtraction") + 1);
	strncpy(toReturn->choices[2], "Subtraction", sizeof("Subtraction\0"));

	toReturn->choices[3] = (char*) malloc(sizeof("Multiplication") + 1);
	strncpy(toReturn->choices[3], "Multiplication", sizeof("Multiplication"));

	toReturn->choices[4] = (char*) malloc(sizeof("Division") + 1);
	strncpy(toReturn->choices[4], "Division", sizeof("Multiplication"));

	toReturn->choices[5] = (char*) malloc(sizeof("Modulo") + 1);
	strncpy(toReturn->choices[5], "Modulo", sizeof("Modulo"));

	toReturn->choices[6] = (char*) malloc(sizeof("Reverse Input") + 1);
	strncpy(toReturn->choices[6], "Reverse Input", sizeof("Reverse Input"));

	return toReturn;
}










//setting entries in the menu structure
void setEntries(char* argv[], int argc, struct menu* toEdit)
{
	char* ep;
	toEdit->numEntries = argc - 1;

	toEdit->entries = (long*) malloc(sizeof(long)*toEdit->numEntries);

	for(int i = 1; i < argc; ++i)
		toEdit->entries[i - 1] = strtol(argv[i], &ep, 16);
}









//prints the entries that were put in as command line arguments
void printEntries(struct menu* toPrint)
{
	for(int i = 0; i < toPrint->numEntries; ++i)
		printf("\n%ld", toPrint->entries[i]);
}


//prints the menu options
void printMenu(struct menu* toPrint)
{
	printf("\n");
	for(int i = 0; i < toPrint->items; ++i)
		printf("%d. %s\n", i, toPrint->choices[i]);
}






float exit_prog(menu* toSet)
{
	toSet->isRunning = false;
	return -1;
}

float addition(struct menu* myMenu)
{
	printf("\n");

	long toReturn = 0;
	for(int i = 0; i < myMenu->numEntries; ++i)
	{
		printf("%lx", myMenu->entries[i]);
		if(i == myMenu->numEntries - 1)
			printf(" = ");
		else
			printf(" + ");
		toReturn += myMenu->entries[i];
	}
	printf("%ld\n", toReturn);
	return toReturn;
}

float subtraction(struct menu* myMenu)
{

	printf("\n");
	long toReturn = 0;
	for(int i = 0; i < myMenu->numEntries; ++i)
	{
		printf("%lx", myMenu->entries[i]);
		if(i == myMenu->numEntries - 1)
			printf(" = ");
		else
			printf(" - ");
		toReturn -= myMenu->entries[i];
	}
	printf("%ld\n", toReturn);
	return toReturn;
}

float multiplication(struct menu* myMenu)
{
	printf("\n");
	long toReturn = 1;
	for(int i = 0; i < myMenu->numEntries; ++i)
	{
		printf("%ld", myMenu->entries[i]);
		if(i == myMenu->numEntries - 1)
			printf(" = ");
		else
			printf(" * ");
		toReturn *= myMenu->entries[i];
	}
	printf("%ld\n", toReturn);
	return toReturn;
}

float division(struct menu* myMenu)
{
	printf("\n");

	if(myMenu->numEntries < 2)
	{
		printf("\nCannot divide, not enough numbers...");
		return -1;		
	}

	//gotta check to see if we are dividing by zero
	if(myMenu->entries[1] == 0)
		printf("Cannot divide by zero");
	else
		return myMenu->entries[0] / myMenu->entries[1];

	return -1;
}


float modulo(struct menu* myMenu)
{
	printf("\n");
	long toReturn = 0;
	for(int i = 0; i < myMenu->numEntries; ++i)
	{
		printf("%lx", myMenu->entries[i]);
		if(i == myMenu->numEntries - 1)
			printf(" = ");
		else
			printf(" %% ");
		toReturn %= myMenu->entries[i];
	}
	printf("%ld\n", toReturn);
	return toReturn;


}

float reverse(menu* myMenu)
{

}

typedef float FDT(menu* myMenu);



int main(int argc, char* argv[])
{
	if(argc > 16 || argc == 1)
	{
		printf("Please input valid numbers");
		exit(EXIT_FAILURE);
	}


	struct menu* myMenu = newMenu();

	setEntries(argv, argc, myMenu);


	FDT* function_table[7] = {
		exit_prog,
		addition,
		subtraction,
		multiplication,
		division,
		modulo,
		reverse
	};

	char input;
	while(myMenu->isRunning)
	{

		printMenu(myMenu);
		printf("\nMenu Item: ");
		
		input = getchar();

		switch(input)
		{
			case '1':
				function_table[1](myMenu);
				break;

			case '2':
				function_table[2](myMenu);
				break;

			case '3':
				function_table[3](myMenu);
				break;

			case '4':
				function_table[4](myMenu);
				break;	

			case '5':
				function_table[5](myMenu);
				break;

			case '6':
				function_table[6](myMenu);
				break;
			case '0':
				function_table[0](myMenu);
				break;
			default:
				printf("\nPlease enter a valid number...\n");
				break;
		}

		while((input = getchar()) != '\n' && input != EOF);
	}

}

