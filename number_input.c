#include <stdio.h>
#include <stdlib.h>

void readIntsFromFile(char filename[], int *store);

int *pIntegers, integersCount;
int dynamicArraySizeModifier = 10;

int main (int argc, char *argv[]) {
  if (argc <= 1) {
    printf("Missing file name argument!");
    return -1;
  }
  readIntsFromFile(argv[1], pIntegers);

  // Print the results
  printf("%d", pIntegers[0]);
  for (int i= 1; i < integersCount; i++) {
    printf(" %d", pIntegers[i]);
  }
  printf("\nThe file contained %d integers.\n", integersCount);
}

void readIntsFromFile(char filename[], int *store) {
  integersCount = 0;
  FILE* file = fopen (filename, "r");
  int i = 0, size = dynamicArraySizeModifier;
  if(NULL == (pIntegers = calloc(size, sizeof(int)))){
    printf("calloc failed");
    return;
  }

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
