#include "../include/sblib.h"
#include <stdio.h>
#include <stdlib.h>

void sbIntArrayInit(SBIntArray *array, int size) {
  array->data = malloc(sizeof(int) * size);
  array->size = size;
}

void sbIntArray2DInit(SBIntArray2D *array, int rows, int cols) {
  array->rows = rows;
  array->cols = cols;
  array->data = malloc(sizeof(int *) * rows);
  for (int i = 0; i < rows; i++) {
    array->data[i] = malloc(sizeof(int) * cols);
  }
}

void sbCsvToArray(SBIntArray2D *array, const char *filename) {
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
