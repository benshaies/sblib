#include "../include/sblib.h"
#include <stdlib.h>

LevelData LevelDataInit(int layers, Texture2D texture, int arrayRows,
                        int arrayCols) {
  LevelData levelData;
  levelData.layerCount = layers;
  levelData.texture = texture;

  levelData.array = malloc(layers * sizeof(intArray2D));
  for (int i = 0; i < layers; i++) {
    intArray2DInit(&levelData.array[i], arrayRows, arrayCols);
  }

  return levelData;
}
