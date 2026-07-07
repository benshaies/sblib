#ifndef SBTILES_H
#define SBTILES_H

#include "../include/sblib.h"
#include <raylib.h>

typedef struct {
  int currentLayer;
  Vector2 currentDrawSize;
} SBTILES;

// Initialize sbTiles struct
void sbTilesInit();

// All main updates to sbTiles
void sbTilesUpdate(LevelData *currentLevel, Vector2 mousePos);

// All drawing to sbTiles
void sbTilesDraw(LevelData currentLevel, int drawTileWidth, int drawTileHeight);

#endif
