#include "../include/sblib.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

SB_Level SB_Level_Init(int layers, int arrayRows, int arrayCols,
                       const char *tilesetName, int tileSize) {
  SB_Level levelData;
  levelData.layerCount = layers;

  levelData.layer = malloc(layers * sizeof(SB_IntArray2D));
  for (int i = 0; i < layers; i++) {
    SB_IntArray2D_Init(&levelData.layer[i], arrayRows, arrayCols);
  }

  strcpy(levelData.tilesetName, tilesetName);
  levelData.tileSize = tileSize;

  return levelData;
}


void SB_Level_Draw(SB_Level level, SB_Tileset tileset, int drawTileWidth, int drawTileHeight,
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
            (tile % tileset.cols) * tileset.tileSize,
            (tile / tileset.cols) * tileset.tileSize,
            tileset.tileSize,
            tileset.tileSize,
        };
        DrawTexturePro(tileset.texture, sourceRec,
                       (Rectangle){j * drawTileWidth, i * drawTileHeight,
                                   drawTileWidth, drawTileHeight},
                       (Vector2){0, 0}, 0.0f, WHITE);
      }
    }
  }
}

<<<<<<< HEAD
=======
<<<<<<< Updated upstream
=======
>>>>>>> 398c4ea (Working draw visible function tested and working)
void SB_Level_Draw_Visible(SB_Level level, SB_Tileset tileset, int drawTileWidth, int drawTileHeight, int drawLayer, Rectangle visibleArea){

  bool noLayering = false;
  if (drawLayer != -1)
    noLayering = true;

  int startLayer = noLayering ? drawLayer : 0;
  int endLayer = noLayering ? drawLayer + 1 : level.layerCount;

<<<<<<< HEAD
  int startX = (int)floorf(visibleArea.x / drawTileWidth);
  int endX   = (int)ceilf((visibleArea.x + visibleArea.width) / drawTileWidth);

  int startY = (int)floorf(visibleArea.y / drawTileHeight);
  int endY   = (int)ceilf((visibleArea.y + visibleArea.height) / drawTileHeight);

  // Clamp to the map (use your actual level dimension fields)
  if (startX < 0) startX = 0;
  if (startY < 0) startY = 0;
  if (endX > level.layer->cols)  endX = level.layer->cols;
  if (endY > level.layer->rows) endY = level.layer->rows;

  for(int l = startLayer; l < endLayer; l++){

    for(int y = startY; y < endY; y++){
      for(int x = startX; x < endX; x++){

=======
  int startX = (int)(visibleArea.x / drawTileWidth);
  int endX = (int)(startX + (visibleArea.width / drawTileWidth));

  int startY = (int)(visibleArea.y / drawTileHeight);
  int endY = (int)(startY + (visibleArea.height / drawTileHeight));

  if(startX < 0) startX = 0;
  if(startY < 0) startY = 0;
  if(endX > level.layer[0].cols) endX = level.layer[0].cols;
  if(endY > level.layer[0].rows) endY = level.layer[0].rows;

  for(int l = startLayer; l < endLayer; l++){

    for(int y = startY; y < endY+1; y++){
      for(int x = startX; x < endX+1; x++){
        
>>>>>>> 398c4ea (Working draw visible function tested and working)
        int tile = level.layer[l].data[y][x];
        if (tile < 0)
          continue;

        Rectangle sourceRec = {
            (tile % tileset.cols) * tileset.tileSize,
            (tile / tileset.cols) * tileset.tileSize,
            tileset.tileSize,
            tileset.tileSize,
        };
        DrawTexturePro(tileset.texture, sourceRec,
                       (Rectangle){x * drawTileWidth, y * drawTileHeight,
                                   drawTileWidth, drawTileHeight},
                       (Vector2){0, 0}, 0.0f, WHITE);
<<<<<<< HEAD
      }
    }
  }
}

=======

      }

    }
  }

  printf("%d %d \n", startX, startY);


}

>>>>>>> Stashed changes
>>>>>>> 398c4ea (Working draw visible function tested and working)
void SB_Level_Free(SB_Level *level) {
  for (int i = 0; i < level->layerCount; i++) {
    free(level->layer[i].data);
    level->layer[i].data = NULL;
  }

  free(level->layer);
  level->layer = NULL;
  level->layerCount = 0;

}

// Saving Function
void SB_Level_Save(SB_Level level, const char *filename) {
  FILE *file;

  file = fopen(filename, "w");

  fprintf(file, "LAYER_COUNT: %d", level.layerCount);
  fprintf(file, "\nTILESET_FILENAME: %s", level.tilesetName);
  fprintf(file, "\nTILESET_TILESIZE: %d", level.tileSize);
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
SB_Level SB_Level_Load(const char *filepath) {
  FILE *file;
  file = fopen(filepath, "r");

  SB_Level level = {0};

  if (file == NULL) {
    printf("SB_LEVEL LOADING ERROR: Unable to Open / Find file\n");
    level.emptyReturn = true;
    return level;
  }

  int tempLayerCount;
  int tempTileSize;
  char tempFileName[256];
  int tempArrayRows;
  int tempArrayCols;

  fscanf(file, "LAYER_COUNT: %d\n", &tempLayerCount);

  fscanf(file, "TILESET_FILENAME: %63[^\n]\n", tempFileName);
  fscanf(file, "TILESET_TILESIZE: %d\n", &tempTileSize);

  fscanf(file, "ARRAY_ROWS: %d\n", &tempArrayRows);
  fscanf(file, "ARRAY_COLS: %d\n", &tempArrayCols);

  level.layerCount = tempLayerCount;

  // Allocating memory for array data
  level.layer = malloc(tempLayerCount * sizeof(SB_IntArray2D));
  for (int i = 0; i < level.layerCount; i++) {
    SB_IntArray2D_Init(&level.layer[i], tempArrayRows, tempArrayCols);
    level.layer[i].rows = tempArrayRows;
    level.layer[i].cols = tempArrayCols;
  }

  for (int i = 0; i < level.layerCount; i++) {
    char layerHeader[32];
    fscanf(file, " %31[^:]:", layerHeader);

    for (int row = 0; row < tempArrayRows; row++) {
      for (int col = 0; col < tempArrayCols; col++) {
        int value;
        fscanf(file, "%d,", &value);
        level.layer[i].data[row][col] = value;
      }
    }
  }

  level.tileSize = tempTileSize;
  strcpy(level.tilesetName, tempFileName);

  printf("SB_LEVEL FILE LOADED: SUCCESS\n");

  return level;
}

SB_Tileset SB_Tileset_Init(const char *assetDir, const char *fileName, int tileSize) {
    SB_Tileset tileset = {0};

    snprintf(tileset.fileName, sizeof(tileset.fileName), "%s", fileName);

    char path[512];
    snprintf(path, sizeof(path), "%s/%s", assetDir, fileName);
    tileset.texture = LoadTexture(path);

    if (tileset.texture.id == 0 || tileSize <= 0) {
        TraceLog(LOG_ERROR, "SB_Tileset: failed to load %s", path);
        return tileset;
    }

    tileset.tileSize = tileSize;
    tileset.cols = tileset.texture.width / tileSize;
    tileset.rows = tileset.texture.height / tileSize;

    return tileset;
}

void SB_Tileset_Free(SB_Tileset *tileset){
  UnloadTexture(tileset->texture);
}
