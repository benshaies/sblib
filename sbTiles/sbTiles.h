#ifndef SBTILES_H
#define SBTILES_H

#include "../include/sblib.h"
#include <raylib.h>

typedef struct {
  int currentLayer;
  Vector2 currentDrawSize;

} SBTILES;

void sbTilesInit();

void sbTilesUpdate(LevelData *currentLevel, Vector2 mousePos);

void sbTilesDraw(LevelData currentLevel, int drawTileWidth, int drawTileHeight);

#endif
