#include <stdio.h>
#include <stdlib.h>

void readIntsFromFile(char[], int*);
void sortIntegers(int *, int);
void search(int, int*);

// Where to store integers and number of integers stored
int *pIntegers, integersCount;
// Amount to expand memory allocation
const int dynamicArraySizeModifier = 10;

int main (int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s FILENAME\n", argv[0]);
    return -1;
  }
  // Takes filename and pointer to store integers as parameters
  readIntsFromFile(argv[1], pIntegers);

  // Takes pointer to sort and number of integers as parameters
  sortIntegers(pIntegers, integersCount);

  // Ask user what to search for
  printf("Please input an integer for search: ");
  int input;
  scanf("%d", &input);
  if (input == 0) {
    printf("Input was '0', exiting.");
    return 0;
  }
  int *result = malloc(sizeof(int));
  *result = -1;
  // Do search
  search(input, result);
  if (*result < 0) {
    printf("%d not found", input);
  } else {
    printf("'%d' found at index: %d", input, *result);
  }

  // Cleanup. Not sure if this is needed? Google said it depends on the OS.
  free(pIntegers);
  free(result);
}

void readIntsFromFile(char filename[], int *store) {
  // Resets counter
  integersCount = 0;
  FILE* file = fopen (filename, "r");
  int i = 0, size = dynamicArraySizeModifier;
  if(NULL == (pIntegers = calloc(size, sizeof(int)))){
    printf("calloc failed");
    return;
  }

  // Reads fro file
  while (fscanf (file, "%d", &i) != EOF) {
    integersCount++;
    // Need to expand pIntegers?
    if (size <= integersCount) {
      size += dynamicArraySizeModifier; // Expand memory of 'pIntegers' by 'dynamicArraySizeModifier'
      if (NULL == (pIntegers = realloc(pIntegers, size*sizeof(int)))) {
        printf("realloc failed\n");
        return;
      }
    }
    // Store int in pointer
    pIntegers[integersCount - 1] = i;
  }
  fclose (file);

  // Make pIntegers as small as possible
  if (size != integersCount) {
    if (NULL == (pIntegers = realloc(pIntegers, integersCount*sizeof(int)))) {
      printf("realloc failed\n");
      return;
    }
  }
}

void sortIntegers(int *toSort, int size) {
  // Bubble sort
  int max = size - 1, tmp;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < max; j++) {
      if (toSort[j] > toSort[j+1]) {
        tmp = toSort[j];
        toSort[j] = toSort[j+1];
        toSort[j+1] = tmp;
      }
    }
    max--;
  }
}

void search(int searchFor, int *result) {
  // Binary search
  for (int i = 0; i < integersCount; i++) {
    if (pIntegers[i] == searchFor) {
      *result = i;
      return;
    }
  }
}
