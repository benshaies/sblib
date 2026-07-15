#include "../include/sblib.h"
#include <raylib.h>
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

void levelDataDraw(LevelData level, int drawTileWidth, int drawTileHeight,
                   int drawLayer) {

  bool noLayering = false;
  if (drawLayer != -1)
    noLayering = true;

  int startLayer = noLayering ? drawLayer : 0;
  int endLayer = noLayering ? drawLayer + 1 : level.layerCount;

  for (int l = startLayer; l < endLayer; l++) {
    for (int i = 0; i < level.layer[l].rows; i++) {
      for (int j = 0; j < level.layer[l].cols; j++) {
        int tile = level.layer[l].data[i][j];
        if (tile < 0)
          continue;

        Rectangle sourceRec = {
            (tile % level.tileset.width) * level.tileset.tileSize,
            (tile / level.tileset.width) * level.tileset.tileSize,
            level.tileset.tileSize,
            level.tileset.tileSize,
        };
        DrawTexturePro(level.tileset.texture, sourceRec,
                       (Rectangle){j * drawTileWidth, i * drawTileHeight,
                                   drawTileWidth, drawTileHeight},
                       (Vector2){0, 0}, 0.0f, WHITE);
      }
    }
  }
}

void levelDataFree(LevelData *level) {
  for (int i = 0; i < level->layerCount; i++) {
    free(level->layer[i].data);
    level->layer[i].data = NULL;
  }

  free(level->layer);
  level->layer = NULL;
  level->layerCount = 0;
}

Tileset tilesetInit(Texture2D texture, int width, int height, int tileSize) {
  Tileset tileset;

  tileset.texture = texture;
  tileset.width = width;
  tileset.height = height;
  tileset.tileSize = tileSize;

  return tileset;
}
