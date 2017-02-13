/*David Velasquez
Operating Systems - Proj1 - Simple Shell
Due: February 14th, 2017*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <process.h>
#include "functions.h"

int main()
{
	int i = 0, j, k, numArgs = 0;
	char ** argArray, ** argArrayFree = NULL;
	printf("\nWelcome to the Cool Shell\n\n");

	char ** pathv = (char**)malloc(64 * sizeof(char*));	//init number of paths (64)
	for (i = 0; i < 64; i++)							//init the path length of each path in the array (128 chars)
		pathv[i] = (char*)malloc(128);					

	parsePath(pathv);

	while (1)
	{
		char * input = getUserInput();			//prompt function for user input
		char * savedInput = input;				//free this memory allocated at the end
		char * command;							//stores only the command (not the arguments)

		command = parseCommand(input);
		//char * fullCmdName = lookupPath(command, pathv);	//needed once path searching works
		for (k = 0; k < strlen(command); k++)	//removes command from input and leaves arguments
			input++;

		numArgs = getNumArgs(input);

		if (numArgs > 0)
		{
			argArray = getArgArray(input);
			argArrayFree = argArray;
		}

		/*if (strcmp(command, "exit") == 0)
			exitShell(numArgs);*/

		//start child process
		if (fork() == 0)
		{
			execvp(command, argArray);
			exit(0);	//should not reach here
		}

		//parent process
	

		free(command);
		free(savedInput);
		//free(fullCmdName);
		for (i = 0; i < numArgs; i++)
			free(argArrayFree[i]);

	}

	return 0;
}