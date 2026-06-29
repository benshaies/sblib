#include "../include/sblib.h"
#include <stdlib.h>

LevelData levelDataInit(int layers, Tileset tileset, int arrayRows,
                        int arrayCols) {
  LevelData levelData;
  levelData.layerCount = layers;
  levelData.tileset = tileset;

  levelData.layer = malloc(layers * sizeof(intArray2D));
  for (int i = 0; i < layers; i++) {
    intArray2DInit(&levelData.layer[i], arrayRows, arrayCols);
  }

  return levelData;
}

void levelDataDraw(LevelData *level, Camera2D cam) {}

Tileset tilesetInit(Texture2D texture, int width, int height, int tileWidth,
                    int tileHeight) {
  Tileset tileset;

  tileset.texture = texture;
  tileset.width = width;
  tileset.height = height;
  tileset.tileWidth = tileWidth;
  tileset.tileHeight = tileHeight;

  return tileset;
}
