#include "../include/sblib.h"
#include <stdio.h>
#include <stdlib.h>

void intArrayInit(intArray *array, int size) {
  array->data = malloc(sizeof(int) * size);
  array->size = size;

  for (int i = 0; i < size; i++) {
    array->data[i] = 0;
  }
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
      array->data[y][x] = 0;
    }
  }
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
