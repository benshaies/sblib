#ifndef SBTILES_H
#define SBTILES_H

#include "../include/sblib.h"

void sbTilesInit();

void sbTilesUpdate(LevelData *currentLevel, bool active, Vector2 mousePos);

void sbTilesDraw(LevelData currentLevel);

#endif
