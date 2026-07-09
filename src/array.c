#include "../include/sblib.h"
#include <stdio.h>
#include <stdlib.h>

void intArrayInit(intArray *array, int size) {
  array->data = malloc(sizeof(int) * size);
  array->size = size;

  for (int i = 0; i < size; i++) {
    array->data[i] = -1;
  }
}

void intArrayFree(intArray *array) {
  free((array->data));
  array->data = NULL;
  array->size = 0;
}

void intArray2DInit(intArray2D *array, int rows, int cols) {
  array->rows = rows;
  array->cols = cols;
  array->data = malloc(sizeof(int *) * rows);
  for (int i = 0; i < rows; i++) {
    array->data[i] = malloc(sizeof(int) * cols);
  }

  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      array->data[y][x] = -1;
    }
  }
}

void intArray2DFree(intArray2D *array) {
  if (array == NULL || array->data == NULL)
    return;

  // 1. Free each individual row block
  for (int i = 0; i < array->rows; i++) {
    free(array->data[i]);
    array->data[i] = NULL; // Clear the pointer for safety
  }

  // 2. Free the master list pointer array
  free(array->data);
  array->data = NULL; // Clear the master pointer

  // 3. Reset dimensions
  array->rows = 0;
  array->cols = 0;
}

void csvToArray(intArray2D *array, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("Failed to open %s\n", filename);
    return;
  }

  for (int y = 0; y < array->rows; y++) {
    for (int x = 0; x < array->cols; x++) {
      fscanf(file, "%d,", &array->data[y][x]);
    }
  }

  fclose(file);
}
