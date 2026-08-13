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

// Saving Functions
void saveIntArray2D(FILE *file, SB_IntArray2D array) {
  fwrite(&array.cols, sizeof(int), 1, file);
  fwrite(&array.rows, sizeof(int), 1, file);

  for (int y = 0; y < array.rows; y++) {
    fwrite(array.data[y], sizeof(int), array.cols, file);
  }
}

void saveTileset(FILE *file, SB_Tileset tileset) {

  if ((tileset.tileSize > 0)) {
    int len = strlen(tileset.texturePath);

    fwrite(&len, sizeof(int), 1, file);

    fwrite(tileset.texturePath, sizeof(char), len + 1, file);

    fwrite(&tileset.tileSize, sizeof(int), 1, file);
  } else {
    tileset.rows = 0;
    tileset.cols = 0;
    tileset.tileSize = 0;
  }
}

void SB_Level_Save(SB_Level level, const char *filename) {
  FILE *file = fopen(filename, "wb");

  if (file == NULL) {
    printf("FILE FAILED TO OPEN");
    return;
  }

  // Level Array Saving
  fwrite(&level.layerCount, sizeof(int), 1, file);

  for (int l = 0; l < level.layerCount; l++) {
    saveIntArray2D(file, level.layer[l]);
  }

  // Saving tileset
  saveTileset(file, level.tileset);

  fclose(file);
}

// Loading functions
SB_IntArray2D loadIntArray2D(FILE *file) {
  SB_IntArray2D array;

  fread(&array.cols, sizeof(int), 1, file);
  fread(&array.rows, sizeof(int), 1, file);

  array.data = malloc(sizeof(int *) * array.rows);
  for (int i = 0; i < array.rows; i++) {
    array.data[i] = malloc(sizeof(int) * array.cols);
    fread(array.data[i], sizeof(int), array.cols, file);
  }

  return array;
}

SB_Tileset loadTileset(FILE *file) {
  SB_Tileset tileset;
  int len;

  fread(&len, sizeof(int), 1, file);
  fread(tileset.texturePath, sizeof(char), len + 1, file);
  fread(&tileset.tileSize, sizeof(int), 1, file);

  tileset.texture = LoadTexture(tileset.texturePath);
  tileset.cols = tileset.texture.width / tileset.tileSize;
  tileset.rows = tileset.texture.height / tileset.tileSize;

  return tileset;
}

SB_Level SB_Level_Load(const char *filepath) {
  FILE *file = fopen(filepath, "rb");

  SB_Level level = {0};

  if (!file) {
    printf("FILE FAILED TO OPEN: %s\n", filepath);
    return level;
  }

  fread(&level.layerCount, sizeof(int), 1, file);

  level.layer = malloc(sizeof(SB_IntArray2D) * level.layerCount);
  for (int l = 0; l < level.layerCount; l++) {
    level.layer[l] = loadIntArray2D(file);
  }

  level.tileset = loadTileset(file);

  fclose(file);

  return level;
}

SB_Tileset SB_Tileset_Init(const char *texturePath, int tileSize) {
  SB_Tileset tileset;

  tileset.texture = LoadTexture(texturePath);
  strcpy(tileset.texturePath, texturePath);
  tileset.tileSize = tileSize;
  tileset.cols = tileset.texture.width / tileset.tileSize;
  tileset.rows = tileset.texture.height / tileset.tileSize;

  return tileset;
}
