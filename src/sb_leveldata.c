#include "../include/sblib.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SB_Level SB_Level_Init(int layers, SB_Tileset tileset, int arrayRows,
                       int arrayCols) {
  SB_Level levelData;
  levelData.layerCount = layers;
  levelData.tileset = tileset;

  levelData.layer = malloc(layers * sizeof(SB_IntArray2D));
  for (int i = 0; i < layers; i++) {
    SB_IntArray2D_Init(&levelData.layer[i], arrayRows, arrayCols);
  }

  return levelData;
}

void SB_Level_Draw(SB_Level level, int drawTileWidth, int drawTileHeight,
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
            (tile % level.tileset.cols) * level.tileset.tileSize,
            (tile / level.tileset.cols) * level.tileset.tileSize,
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

void SB_Level_Free(SB_Level *level) {
  for (int i = 0; i < level->layerCount; i++) {
    free(level->layer[i].data);
    level->layer[i].data = NULL;
  }

  free(level->layer);
  level->layer = NULL;
  level->layerCount = 0;

  UnloadTexture(level->tileset.texture);
}

// Saving Function
void SB_Level_Save(SB_Level level, const char *filename) {
  FILE *file;

  file = fopen(filename, "w");

  fprintf(file, "LAYER_COUNT: %d", level.layerCount);
  fprintf(file, "\nTILESET_FILENAME: %s", level.tileset.fileName);
  fprintf(file, "\nTILESET_TILESIZE: %d", level.tileset.tileSize);
  fprintf(file, "\nARRAY_ROWS: %d", level.layer->rows);
  fprintf(file, "\nARRAY_COLS: %d", level.layer->cols);

  for (int l = 0; l < level.layerCount; l++) {
    fprintf(file, "\nLAYER_%d:", l);

    for (int y = 0; y < level.layer[l].rows; y++) {
      fprintf(file, "\n");
      for (int x = 0; x < level.layer[l].cols; x++) {
        if (x < level.layer[l].cols - 1) {
          fprintf(file, "%d,", level.layer[l].data[y][x]);
        } else {
          fprintf(file, "%d", level.layer[l].data[y][x]);
        }
      }
    }
  }

  fclose(file);

  printf("\nLEVEL FILE SAVED: %s", filename);
}

// Loading function
SB_Level SB_Level_Load(const char *filepath, bool sbTilesLoading) {}

SB_Tileset SB_Tileset_Init(const char *fileName, int tileSize) {
  SB_Tileset tileset;

  char path[256];
  strcpy(tileset.fileName, fileName);

  snprintf(path, sizeof(path), "assets/%s", tileset.fileName);
  tileset.texture = LoadTexture(path);

  tileset.tileSize = tileSize;
  tileset.cols = tileset.texture.width / tileset.tileSize;
  tileset.rows = tileset.texture.height / tileset.tileSize;

  return tileset;
}
