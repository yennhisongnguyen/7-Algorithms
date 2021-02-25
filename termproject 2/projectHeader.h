//typedefs

//definitions
#define MAX_LEN 100  
// boolean
#define FALSE           0
#define TRUE            1

//prototypes
 
//Call this function when you need a random number
//for your integer sorts
int randNum();

//sorting prototypes
//quick sort 
//int
int partition_int (int arr[], int low, int high);
void quickSort_int(int arr[], int low, int high);
//string
int partition_str (char arr[][MAX_LEN], int low, int high);
void quickSort_str(char arr[][MAX_LEN], int low, int high);

//merge sort 
//int
void merge_int(int arr[],int low,int mid,int high);
void mergeSort_int(int arr[],int low,int high);
//str
void merge_str(char arr[][MAX_LEN],int low,int mid,int high);
void mergeSort_str(char arr[][MAX_LEN],int low,int high);

//radix sort
//int
void countSort(int arr[], int n, int exp);
int getMax(int arr[], int n);
void radixSort_int(int arr[], int n);
//str
void radixSort_str(char **strings, size_t len);

//heap sort
//int
void heapify(int arr[], int n, int i);
void heapSort_int(int arr[], int n);
//str
void heapSort_str(char list[][MAX_LEN], int n);

//insertion sort
//str
void insertionSort_str(char list[][MAX_LEN], int n);
//int
void insertionSort_int(int arr[], int n);

//selection sort
//int
void selectionSort_int(int arr[], int n);
//str
void selectionSort_str(char arr[][MAX_LEN], int n);

//Search algorithms
//linear search
//int linearSearchIterative_int(int data[][10], int n, int target);

//binary search
//int BinarySearchIterative_int(int data[][10], int n, int target);

void clearbuff();