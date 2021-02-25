# Define the list of .o files for project
projectOBJECTS = termproject2Driver.o randomgenlib.o heapSort_int.o heapSort_str.o insertionSort_int.o insertionSort_str.o mergeSort_int.o mergeSort_str.o quickSort_int.o quickSort_str.o radixSort_int.o selectionSort_int.o selectionSort_str.o
projectINCLUDES = projectHeader.h

# Default Rules for building each .o
%.o: %.c ${projectINCLUDES}
	gcc -g -c $<

# Rule for building the executable
project: ${projectOBJECTS}
	gcc -g -o project ${projectOBJECTS}

# Special rule to remove the .o files
clean:
	rm -f ${projectOBJECTS}
