#ifndef SBTILES_H
#define SBTILES_H

#include "../include/sblib.h"
#include <raylib.h>

typedef struct {
  int currentLayer;
  Vector2 currentDrawSize;

  int selectedTile;

  bool showTileSelection;
} SBTILES;

typedef enum {
  TILE_SELECTION,
  LEVEL_EDITING,

} SBT_STATE;

// Initialize sbTiles struct
void sbTilesInit();

// All main updates to sbTiles
void sbTilesUpdate(LevelData *currentLevel, Vector2 mousePos);

// All drawing to sbTiles
void sbTilesDraw(LevelData currentLevel, int drawTileWidth, int drawTileHeight);

#endif
