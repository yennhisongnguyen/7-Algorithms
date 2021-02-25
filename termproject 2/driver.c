#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projectHeader.h"
#include <time.h>

//Prototypes
void processCMDArgs(int argc, char * argv[]);
void printJobStatus();

//Global Variables
//0 == print sorted array, 1 == print time table
int printType;

//0 == integers, 1 == strings
int sortType;

//Sorting Algorithm
//1 == quickSort, 2 == mergeSort, 3 == radixSort, 
//4 == heapSort, 5 == insertionSort, 6 == selectionSort
//7 == test all algorithms
int sortAlg;

//Number of Trials
int numTrials;

//Number of array sizes
int numArraySizes;

//Array sizes
int * arraySizes;

int main(int argc, char * argv[]) {
	
	processCMDArgs(argc, argv);

	//For debugging purposes.
	//Remove all printJobStatus() calls before creating
	//final output and before submitting.
	printJobStatus();


	/*
		It is up to you to implement the rest of the project.

		processCMDArgs will reject array sizes larger than 75000.
		If you want to do the extra credit, modify processCMDArgs
		to accept the larger array sizes.

		For sorting strings:
			Create the array for strings like this:
				char array[arraySizes[numExperiments-1]][MAX_LEN];


			This will create an array that can hold the largest
			number of inputs.  Using this larger array to process
			smaller number of inputs will be ok.

			**Declare the string array ONCE at the top of your
			  function then reuse it.  DO NOT declare a string
			  array for each array size.**

			You do not need to free this type of variable.

			radixSort on strings will not work with this type of variable.
			radixSort on strings is for extra credit.

		For sorting integers:
			Create the array for ints like this:
				int * array = (int *) malloc (arraySizes[i] * sizeof(int));

			You can create the array, fill it, sort it, then free it
			for each array size.  REMEMBER to free it!

			Use randNum() to get each random number for the integer arrays.

		Google 'c clock' to find out how to time your sorting functions.

		If quick sort and other faster sorts report a time of 0.0, that is ok.
		Report 0.0 if that is the result.  Longer arrays and other sorts should
		produce a visible time.

		Create a data structure to store the results of all your experiments, 
		then print out everything at once.

		To run your program in the background:
			$ nohup ./project # # # # # > output.txt &

		When running in the background and you haven't logged out of the server, 
		to see your currently running programs type:
			$ jobs

		If you have logged out, type:
			$ ps aux | grep 'abc123'

		If you want to kill the ./project process:
			$ kill 'process id number'

		Server Info
		DO NOT use the fox servers for this assignment

		in the lab $ ssh abc123@hen01.cs.utsarr.net
		outside    $ ssh abc123@10.100.240.211

		Email Josh if you crash the server.
	*/


	free(arraySizes);

	return 0;
}









void printJobStatus() {
	int i;

	if (printType == 0) printf("\nprintType:   sorted array\n");
	else printf("printType:   time table\n");

	if (sortType == 0) printf("sortType:    integers\n");
	else printf("sortType:    strings\n");

	switch (sortAlg)
	{
	    case 1:
	    	printf("sortAlg:     quickSort\n");
	        break;
	    case 2:
	    	printf("sortAlg:     mergeSort\n");
	        break;
	    case 3:
	    	printf("sortAlg:     radixSort\n");
	        break;
	    case 4:
	    	printf("sortAlg:     heapSort\n");
	        break;
	    case 5:
	    	printf("sortAlg:     insertionSort\n");
	        break;
	    case 6:
	    	printf("sortAlg:     selectionSort\n");
	        break;
	    case 7:
	    	printf("sortAlg:     test all sorting algorithms\n");
	        break;
	}

	printf("numTrials:   %d\n", numTrials);
	printf("numArraySizes: %d\n", numArraySizes);
	printf("array sizes: ");

	for (i=0; i<numArraySizes; i++) {
		printf("%d  ", arraySizes[i]);
	}

	printf("\n\n");
}


void processCMDArgs(int argc, char * argv[]) {
	int i;
	int temp;

	if (argc < 6) {
		printf("CMD Usage: ./project {printType} {sortType} {sortAlg} {numTrials} {arraySizes...arraySizes}\n");
		exit(0);
	}

	for (i=0; i<argc; i++) {
		//get printType
		if (i == 1) {
			if (argv[i][0] == '0') printType = 0;
			else if (argv[i][0] == '1') printType = 1;
			else {
				printf("CMD Usage: ./project {printType} {sortType} {sortAlg} {numTrials} {arraySizes...arraySizes}\n");
				printf("                     {  0 - 1  }\n");
				exit(0);
			}
		}
		if (i == 2) {
			if (argv[i][0] == '0') sortType = 0;
			else if (argv[i][0] == '1') sortType = 1;
			else {
				printf("CMD Usage: ./project {printType} {sortType} {sortAlg} {numTrials} {arraySizes...arraySizes}\n");
				printf("                                 { 0 - 1  }\n");
				exit(0);
			}
		}
		else if (i == 3) {
			temp = atoi(argv[i]);

			if (temp == 0 || temp < 1 || temp > 7) {
				printf("CMD Usage: ./project {printType} {sortType} {sortAlg} {numTrials} {arraySizes...arraySizes}\n");
				printf("                                            { 1 - 7 }\n");
				exit(0);
			}

			sortAlg = temp;
		}
		else if (i == 4) {
			temp = atoi(argv[i]);

			if (temp == 0 || temp < 1 || temp > 3) {
				printf("CMD Usage: ./project {printType} {sortType} {sortAlg} {numTrials} {arraySizes...arraySizes}\n");
				printf("                                                      {  1 - 3  }\n");
				exit(0);
			}

			numTrials = temp;
		}
	}

	numArraySizes = argc - 5;

	if (numArraySizes <= 0) {
		printf("CMD Usage: at least one array size must be given\n");
		printf("CMD Usage: ./project {printType} {sortType} {sortAlg} {numTrials} {arraySizes...arraySizes}\n");
		printf("                                                                  {   1000 < n < 75000    }\n");
		exit(0);
	}

	arraySizes = (int *) malloc(sizeof(int) * numArraySizes);

	if(arraySizes == NULL) {
		printf("Malloc error\n");
		exit(0);
	}

	for (i=5; i<argc; i++) {
		temp = atoi(argv[i]);

		if (temp == 0 || temp < 1000 || temp > 75000) {
			printf("CMD Usage: ./project {printType} {sortType} {sortAlg} {numTrials} {arraySizes...arraySizes}\n");
			printf("                                                                  {   1000 < n < 75000    }\n");
			free(arraySizes);
			exit(0);
		}

		arraySizes[i-5] = temp;
	}
}





