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

double average(double numArray[], int numTrials);
void printAll(double numArray[], int numTrials, double average, int arraySize);

struct sortIntTimes{
    double trials[5];
    double average;
} quick, quickAll, merge, radix, heap, insertion, selection, all, quickS, mergeS, radixS, heapS, insertionS, selectionS, allS;

int main(int argc, char * argv[]) {
    processCMDArgs(argc, argv);
    printJobStatus();

    int i;
    int j; // j is supposed to keep track of the number of times the whole loop nneds to iterate. by numTrials
    int k; //another loop iterator but this time for storing loops
    int l = 0;

    int size = 0;

    clock_t starttime, endtime;
    double totaltime;

    FILE *fptr = NULL;
    fptr = fopen("last_name.txt", "r");
    char strings[arraySizes[numTrials - 1]][MAX_LEN];
    clock_t begin, end;
    double totalTime;

    while(fgets(&strings[j][l], MAX_LEN, fptr) != NULL && j < arraySizes[numTrials - 1]){
        strings[j][strlen(strings[j]) - 1] = '\0';
        j++;
    }

    if(sortType == 0 && printType == 0){//print sorted integers
        if(sortAlg == 1){//quick
            for(j = 0; j < numArraySizes; j++){
                printf("arraySizes = %d\n", arraySizes[j]);
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                quickSort_int(numArray, 0, n-1);
                for(i = 0; i < arraySizes[j]; i++){
                    printf("Trial[%d] = %d\n", i, numArray[i]);
                }
                free(numArray);
            }
        }
        else if(sortAlg == 2){//merge
            for(j = 0; j < numArraySizes; j++){
                printf("arraySizes = %d\n", arraySizes[j]);
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                mergeSort_int(numArray, 0, n-1);
                for(i = 0; i < arraySizes[j]; i++){
                    printf("Trial[%d] = %d\n", i, numArray[i]);
                }
                free(numArray);
            }
        }
        else if(sortAlg == 3){//radix
            for(j = 0; j < numArraySizes; j++){
                printf("arraySizes = %d\n", arraySizes[j]);
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                radixSort_int(numArray, n-1);
                for(i = 0; i < arraySizes[j]; i++){
                printf("Trial[%d] = %d\n", i, numArray[i]);
                }
                free(numArray);
            }
        }
        else if(sortAlg == 4){//heap
            for(j = 0; j < numArraySizes; j++){
                printf("arraySizes = %d\n", arraySizes[j]);
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                heapSort_int(numArray, n-1);
                for(i = 0; i < arraySizes[j]; i++){
                printf("Trial[%d] = %d\n", i, numArray[i]);
                }
                free(numArray);
            }
        }
        else if(sortAlg == 5){//insertion
            for(j = 0; j < numArraySizes; j++){
                printf("arraySizes = %d\n", arraySizes[j]);
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                insertionSort_int(numArray, n-1);
                for(i = 0; i < arraySizes[j]; i++){
                printf("Trial[%d] = %d\n", i, numArray[i]);
                }
                free(numArray);
            }
        }
        else if(sortAlg == 6){//selection
            for(j = 0; j < numArraySizes; j++){
                printf("arraySizes = %d\n", arraySizes[j]);
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                selectionSort_int(numArray, n-1);
                for(i = 0; i < arraySizes[j]; i++){
                printf("Trial[%d] = %d\n", i, numArray[i]);
                }
                free(numArray);
            }
        }
        else if(sortAlg == 7){//all
            for(j = 0; j < numArraySizes; j++){
                printf("arraySizes = %d\n", arraySizes[j]);
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                quickSort_int(numArray, 0, n-1);
                for(i = 0; i < arraySizes[j]; i++){
                    printf("Trial[%d] = %d\n", i, numArray[i]);
                }
                free(numArray);
            }
            for(j = 0; j < numArraySizes; j++){
                printf("arraySizes = %d\n", arraySizes[j]);
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                mergeSort_int(numArray, 0, n-1);
                for(i = 0; i < arraySizes[j]; i++){
                    printf("Trial[%d] = %d\n", i, numArray[i]);
                }
                free(numArray);
            }
            for(j = 0; j < numArraySizes; j++){
                printf("arraySizes = %d\n", arraySizes[j]);
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                radixSort_int(numArray, n-1);
                for(i = 0; i < arraySizes[j]; i++){
                    printf("Trial[%d] = %d\n", i, numArray[i]);
                }
                free(numArray);
            }
            for(j = 0; j < numArraySizes; j++){
                printf("arraySizes = %d\n", arraySizes[j]);
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                heapSort_int(numArray, n-1);
                for(i = 0; i < arraySizes[j]; i++){
                printf("Trial[%d] = %d\n", i, numArray[i]);
                }
                free(numArray);
            }
            for(j = 0; j < numArraySizes; j++){
                printf("arraySizes = %d\n", arraySizes[j]);
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                insertionSort_int(numArray, n-1);
                for(i = 0; i < arraySizes[j]; i++){
                printf("Trial[%d] = %d\n", i, numArray[i]);
                }
                free(numArray);
            }
            for(j = 0; j < numArraySizes; j++){
                printf("arraySizes = %d\n", arraySizes[j]);
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                selectionSort_int(numArray, n-1);
                for(i = 0; i < arraySizes[j]; i++){
                printf("Trial[%d] = %d\n", i, numArray[i]);
                }
                free(numArray);
            }
        }
    }
    else if(sortType == 0 && printType == 1){//print integers timetables
        if(sortAlg == 1){//quick
        printf("Quick Sort - int    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("      Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                for(k = 0; k < numTrials; k++){
                    starttime = clock();
                    quickSort_int(numArray, 0, n-1);
                    endtime = clock();
                    totaltime = ((double)(endtime - starttime)/CLOCKS_PER_SEC);
                    quick.trials[k] = totaltime;
                }
                quick.average = average(quick.trials, numTrials);
                printAll(quick.trials, numTrials, quick.average, arraySizes[j]);
                free(numArray);
            }
        }
        else if(sortAlg == 2){//merge
        printf("Merge Sort - int    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                for(k = 0; k < numTrials; k++){
                    starttime = clock();
                    mergeSort_int(numArray, 0, n-1);
                    endtime = clock();
                    totaltime = ((double)(endtime - starttime)/CLOCKS_PER_SEC);
                    merge.trials[k] = totaltime;
                }
                merge.average = average(merge.trials, numTrials);
                printAll(merge.trials, numTrials, merge.average, arraySizes[j]);
                free(numArray);
            }
        }
        else if(sortAlg == 3){//radix
            printf("Radix Sort - int    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                for(k = 0; k < numTrials; k++){
                    starttime = clock();
                    radixSort_int(numArray, n-1);
                    endtime = clock();
                    totaltime = ((double)(endtime - starttime)/CLOCKS_PER_SEC);
                    radix.trials[k] = totaltime;
                }
                radix.average = average(radix.trials, numTrials);
                printAll(radix.trials, numTrials, radix.average, arraySizes[j]);
                free(numArray);
            }
        }
        else if(sortAlg == 4){//heap
            printf("Heap Sort - int ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                for(k = 0; k < numTrials; k++){
                    starttime = clock();
                    heapSort_int(numArray, n-1);
                    endtime = clock();
                    totaltime = ((double)(endtime - starttime)/CLOCKS_PER_SEC);
                    heap.trials[k] = totaltime;
                }
                heap.average = average(heap.trials, numTrials);
                printAll(heap.trials, numTrials, heap.average, arraySizes[j]);
                free(numArray);
            }
        }
        else if(sortAlg == 5){//insertion
            printf("Insertion Sort - int    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                for(k = 0; k < numTrials; k++){
                    starttime = clock();
                    insertionSort_int(numArray, n-1);
                    endtime = clock();
                    totaltime = ((double)(endtime - starttime)/CLOCKS_PER_SEC);
                    insertion.trials[k] = totaltime;
                }
                insertion.average = average(insertion.trials, numTrials);
                printAll(insertion.trials, numTrials, insertion.average, arraySizes[j]);
                free(numArray);
            }
        }
        else if(sortAlg == 6){//selection
            printf("Selection Sort - int    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                for(k = 0; k < numTrials; k++){
                    starttime = clock();
                    selectionSort_int(numArray, n-1);
                    endtime = clock();
                    totaltime = ((double)(endtime - starttime)/CLOCKS_PER_SEC);
                    selection.trials[k] = totaltime;
                }
                selection.average = average(selection.trials, numTrials);
                printAll(selection.trials, numTrials, selection.average, arraySizes[j]);
                free(numArray);
            }
        }
        else if(sortAlg == 7){//all
            printf("Quick Sort - int    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                for(k = 0; k < numTrials; k++){
                    starttime = clock();
                    quickSort_int(numArray, 0, n-1);
                    endtime = clock();
                    totaltime = ((double)(endtime - starttime)/CLOCKS_PER_SEC);
                    quick.trials[k] = totaltime;
                }
                quick.average = average(quick.trials, numTrials);
                printAll(quick.trials, numTrials, quick.average, arraySizes[j]);
                free(numArray);
            }
            printf("\n");
            printf("Merge Sort - int    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                for(k = 0; k < numTrials; k++){
                    starttime = clock();
                    mergeSort_int(numArray, 0, n-1);
                    endtime = clock();
                    totaltime = ((double)(endtime - starttime)/CLOCKS_PER_SEC);
                    merge.trials[k] = totaltime;
                }
                merge.average = average(merge.trials, numTrials);
                printAll(merge.trials, numTrials, merge.average, arraySizes[j]);
                free(numArray);
            }
            printf("\n");
            printf("Radix Sort - int    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                for(k = 0; k < numTrials; k++){
                    starttime = clock();
                    radixSort_int(numArray, n-1);
                    endtime = clock();
                    totaltime = ((double)(endtime - starttime)/CLOCKS_PER_SEC);
                    radix.trials[k] = totaltime;
                }
                radix.average = average(radix.trials, numTrials);
                printAll(radix.trials, numTrials, radix.average, arraySizes[j]);
                free(numArray);
            }
            printf("\n");
            printf("Heap Sort - int ");
            printf("    Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                for(k = 0; k < numTrials; k++){
                    starttime = clock();
                    heapSort_int(numArray, n-1);
                    endtime = clock();
                    totaltime = ((double)(endtime - starttime)/CLOCKS_PER_SEC);
                    heap.trials[k] = totaltime;
                }
                heap.average = average(heap.trials, numTrials);
                printAll(heap.trials, numTrials, heap.average, arraySizes[j]);
                free(numArray);
            }
            printf("\n");
            printf("Insertion Sort - int ");
            printf("Size   Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                for(k = 0; k < numTrials; k++){
                    starttime = clock();
                    insertionSort_int(numArray, n-1);
                    endtime = clock();
                    totaltime = ((double)(endtime - starttime)/CLOCKS_PER_SEC);
                    insertion.trials[k] = totaltime;
                }
                insertion.average = average(insertion.trials, numTrials);
                printAll(insertion.trials, numTrials, insertion.average, arraySizes[j]);
                free(numArray);
            }
            printf("\n");
            printf("Selection Sort - int ");
            printf("Size   Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                int *numArray = (int *)malloc(arraySizes[j] * sizeof(int));
                int n = arraySizes[j];
                for(l = 0; l < arraySizes[j]; l++){
                    numArray[l] = randNum();
                }
                for(k = 0; k < numTrials; k++){
                    starttime = clock();
                    selectionSort_int(numArray, n-1);
                    endtime = clock();
                    totaltime = ((double)(endtime - starttime)/CLOCKS_PER_SEC);
                    selection.trials[k] = totaltime;
                }
                selection.average = average(selection.trials, numTrials);
                printAll(selection.trials, numTrials, selection.average, arraySizes[j]);
                free(numArray);
            }
        }
    }
    else if(sortType == 1 && printType == 0){//print sorted strings
        if(sortAlg == 1){//quick
            for(j = 0; j < numArraySizes; j++){
                int n = arraySizes[j];
                printf("arraySizes = %d\n", arraySizes[j]);
                quickSort_str(strings, 0, n-1);
                for(i = 0; i < arraySizes[j]; ++i){
                    printf("char[%d] %s\n", i, strings[i]);
                }
            }
        }
        else if(sortAlg == 2){//merge
            for(j = 0; j < numArraySizes; j++){
                int n = arraySizes[j];
                printf("arraySizes = %d\n", arraySizes[j]);
                mergeSort_str(strings, 0, n-1);
                for(i = 0; i < arraySizes[j]; ++i){
                    printf("char[%d] %s\n", i, strings[i]);
                }
            }
        }
        else if(sortAlg == 3){//radix
            printf("Did not choose to do the extra credit\n");
        }
        else if(sortAlg == 4){//heap
            for(j = 0; j < numArraySizes; j++){
                int n = arraySizes[j];
                printf("arraySizes = %d\n", arraySizes[j]);
                heapSort_str(strings, n);
                for(i = 0; i < arraySizes[j]; ++i){
                    printf("char[%d] %s\n", i, strings[i]);
                }
            }
        }
        else if(sortAlg == 5){//insertion
            for(j = 0; j < numArraySizes; j++){
                int n = arraySizes[j];
                printf("arraySizes = %d\n", arraySizes[j]);
                selectionSort_str(strings, n);
                for(i = 0; i < arraySizes[j]; ++i){
                    printf("char[%d] %s\n", i, strings[i]);
                }
            }
        }
        else if(sortAlg == 6){//selection
            for(j = 0; j < numArraySizes; j++){
                int n = arraySizes[j];
                printf("arraySizes = %d\n", arraySizes[j]);
                insertionSort_str(strings, n-1);
                for(i = 0; i < arraySizes[j]; ++i){
                    printf("char[%d] %s\n", i, strings[i]);
                }
            }
        }
        else if(sortAlg == 7){//all
            for(j = 0; j < numArraySizes; j++){
                int n = arraySizes[j];
                printf("arraySizes = %d\n", arraySizes[j]);
                quickSort_str(strings, 0, n-1);
                for(i = 0; i < arraySizes[j]; ++i){
                    printf("char[%d] %s\n", i, strings[i]);
                }
            }
            for(j = 0; j < numArraySizes; j++){
                int n = arraySizes[j];
                printf("arraySizes = %d\n", arraySizes[j]);
                mergeSort_str(strings, 0, n-1);
                for(i = 0; i < arraySizes[j]; ++i){
                    printf("char[%d] %s\n", i, strings[i]);
                }
            }
            for(j = 0; j < numArraySizes; j++){
                int n = arraySizes[j];
                printf("arraySizes = %d\n", arraySizes[j]);
                heapSort_str(strings, n);
                for(i = 0; i < arraySizes[j]; ++i){
                    printf("char[%d] %s\n", i, strings[i]);
                }
            }
            for(j = 0; j < numArraySizes; j++){
                int n = arraySizes[j];
                printf("arraySizes = %d\n", arraySizes[j]);
                selectionSort_str(strings, n);
                for(i = 0; i < arraySizes[j]; ++i){
                    printf("char[%d] %s\n", i, strings[i]);
                }
            }
            for(j = 0; j < numArraySizes; j++){
                int n = arraySizes[j];
                printf("arraySizes = %d\n", arraySizes[j]);
                insertionSort_str(strings, n-1);
                for(i = 0; i < arraySizes[j]; ++i){
                    printf("char[%d] %s\n", i, strings[i]);
                }
            }
        }
    }
    else if(sortType == 1 && printType == 1){//print strings timetables
        if(sortAlg == 1){//quick
            printf("Quick Sort - str    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                char smaller[arraySizes[j]][MAX_LEN];
                int n = arraySizes[j];
                for(i = 0; i < arraySizes[k]; i++){
                    strcpy(smaller[i], strings[i]);
                }
                for(k = 0; k < numTrials; k++){
                    begin = clock();
                    quickSort_str(smaller, 0, n-1);
                    end = clock();
                    totalTime = ((double)(end - begin)/CLOCKS_PER_SEC);
                    quickS.trials[k] = totalTime;
                }
            quickS.average = average(quickS.trials, numTrials);
            printAll(quickS.trials, numTrials, quickS.average, arraySizes[j]);
            }
        }
        else if(sortAlg == 2){//merge
            printf("Merge Sort - str    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                char smaller[arraySizes[j]][MAX_LEN];
                int n = arraySizes[j];
                for(i = 0; i < arraySizes[k]; i++){
                    strcpy(smaller[i], strings[i]);
                }
                for(k = 0; k < numTrials; k++){
                    begin = clock();
                    mergeSort_str(smaller, 0, n-1);
                    end = clock();
                    totalTime = ((double)(end - begin)/CLOCKS_PER_SEC);
                    mergeS.trials[k] = totalTime;
                }
            mergeS.average = average(mergeS.trials, numTrials);
            printAll(mergeS.trials, numTrials, mergeS.average, arraySizes[j]);
            }
        }
        else if(sortAlg == 3){//radix
            printf("Did not choose to do the extra credit\n");
        }
        else if(sortAlg == 4){//heap
            printf("Heap Sort - str ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                char smaller[arraySizes[j]][MAX_LEN];
                int n = arraySizes[j];
                for(i = 0; i < arraySizes[k]; i++){
                    strcpy(smaller[i], strings[i]);
                }
                for(k = 0; k < numTrials; k++){
                    begin = clock();
                    heapSort_str(smaller, n);
                    end = clock();
                    totalTime = ((double)(end - begin)/CLOCKS_PER_SEC);
                    heapS.trials[k] = totalTime;
                }
            heapS.average = average(heapS.trials, numTrials);
            printAll(heapS.trials, numTrials, heapS.average, arraySizes[j]);
            }
        }
        else if(sortAlg == 5){//insertion
            printf("Insertion Sort - str    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                char smaller[arraySizes[j]][MAX_LEN];
                int n = arraySizes[j];
                for(i = 0; i < arraySizes[k]; i++){
                    strcpy(smaller[i], strings[i]);
                }
                for(k = 0; k < numTrials; k++){
                    begin = clock();
                    insertionSort_str(smaller, n);
                    end = clock();
                    totalTime = ((double)(end - begin)/CLOCKS_PER_SEC);
                    insertionS.trials[k] = totalTime;
                }
            insertionS.average = average(insertionS.trials, numTrials);
            printAll(insertionS.trials, numTrials, insertionS.average, arraySizes[j]);
            }
        }
        else if(sortAlg == 6){//selection
            printf("Selection Sort - str    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                char smaller[arraySizes[j]][MAX_LEN];
                int n = arraySizes[j];
                for(i = 0; i < arraySizes[k]; i++){
                    strcpy(smaller[i], strings[i]);
                }
                for(k = 0; k < numTrials; k++){
                    begin = clock();
                    selectionSort_str(smaller, n);
                    end = clock();
                    totalTime = ((double)(end - begin)/CLOCKS_PER_SEC);
                    selectionS.trials[k] = totalTime;
                }
            selectionS.average = average(selectionS.trials, numTrials);
            printAll(selectionS.trials, numTrials, selectionS.average, arraySizes[j]);
            }
        }
        else if(sortAlg == 7){//all
            printf("Quick Sort - str    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                char smaller[arraySizes[j]][MAX_LEN];
                int n = arraySizes[j];
                for(i = 0; i < arraySizes[k]; i++){
                    strcpy(smaller[i], strings[i]);
                }
                for(k = 0; k < numTrials; k++){
                    begin = clock();
                    quickSort_str(smaller, 0, n-1);
                    end = clock();
                    totalTime = ((double)(end - begin)/CLOCKS_PER_SEC);
                    quickS.trials[k] = totalTime;
                }
            quickS.average = average(quickS.trials, numTrials);
            printAll(quickS.trials, numTrials, quickS.average, arraySizes[j]);
            }
            printf("\n");
            printf("Merge Sort - str    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                char smaller[arraySizes[j]][MAX_LEN];
                int n = arraySizes[j];
                for(i = 0; i < arraySizes[k]; i++){
                    strcpy(smaller[i], strings[i]);
                }
                for(k = 0; k < numTrials; k++){
                    begin = clock();
                    mergeSort_str(smaller, 0, n-1);
                    end = clock();
                    totalTime = ((double)(end - begin)/CLOCKS_PER_SEC);
                    mergeS.trials[k] = totalTime;
                }
            mergeS.average = average(mergeS.trials, numTrials);
            printAll(mergeS.trials, numTrials, mergeS.average, arraySizes[j]);
            }
            printf("\n");
            printf("Heap Sort - str     ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                char smaller[arraySizes[j]][MAX_LEN];
                int n = arraySizes[j];
                for(i = 0; i < arraySizes[k]; i++){
                    strcpy(smaller[i], strings[i]);
                }
                for(k = 0; k < numTrials; k++){
                    begin = clock();
                    heapSort_str(smaller, n);
                    end = clock();
                    totalTime = ((double)(end - begin)/CLOCKS_PER_SEC);
                    heapS.trials[k] = totalTime;
                }
            heapS.average = average(heapS.trials, numTrials);
            printAll(heapS.trials, numTrials, heapS.average, arraySizes[j]);
            }
            printf("\n");
            printf("Insertion Sort - str    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                char smaller[arraySizes[j]][MAX_LEN];
                int n = arraySizes[j];
                for(i = 0; i < arraySizes[k]; i++){
                    strcpy(smaller[i], strings[i]);
                }
                for(k = 0; k < numTrials; k++){
                    begin = clock();
                    insertionSort_str(smaller, n);
                    end = clock();
                    totalTime = ((double)(end - begin)/CLOCKS_PER_SEC);
                    insertionS.trials[k] = totalTime;
                }
            insertionS.average = average(insertionS.trials, numTrials);
            printAll(insertionS.trials, numTrials, insertionS.average, arraySizes[j]);
            }
            printf("\n");
            printf("Selection Sort - str    ");
            printf("Size    Average ");
            for (i = 0; i < numTrials; i++){
                printf("    Trial[%d]", i);
            }
            printf("\n");
            for(j = 0; j < numArraySizes; j++){
                char smaller[arraySizes[j]][MAX_LEN];
                int n = arraySizes[j];
                for(i = 0; i < arraySizes[k]; i++){
                    strcpy(smaller[i], strings[i]);
                }
                for(k = 0; k < numTrials; k++){
                    begin = clock();
                    selectionSort_str(smaller, n);
                    end = clock();
                    totalTime = ((double)(end - begin)/CLOCKS_PER_SEC);
                    selectionS.trials[k] = totalTime;
                }
            selectionS.average = average(selectionS.trials, numTrials);
            printAll(selectionS.trials, numTrials, selectionS.average, arraySizes[j]);
            }
        }
    }

    free(arraySizes);

    return 0;
}


double average(double array[], int numTrials){
    int i;
    double sum = 0;
    double average;

    for (i = 0; i < numTrials; i++){
        sum += array[i];
    }
    average = sum/numTrials;
    return average;
}

void printAll(double numArray[], int numTrials, double average, int arraySize){
    int i;
    int k;

    printf("                    %d   %f  ", arraySize, average);
    //printf("    ");
    for(k = 0; k < numTrials; k++){
        printf("   %f  ", numArray[k]);
    }
    printf("\n");
}

//gcc randomgenlib.c mergeSort_int.c mergeSort_str.c heapSort_int.c quickSort_int.c radixSort_int.c insertionSort_int.c selectionSort_int.c heapSort_str.c insertionSort_str.c quickSort_str.c selectionSort_str.c termproject2Driver.c -g -o project
//int timetables ./project 1 0 7 3 1000 10000 20000 30000 40000 50000 60000 70000 75000 > outputInt.txt
// char timetbles ./project 1 1 7 3 1000 10000 20000 30000 40000 50000 60000 70000 75000 > outputStr.txt